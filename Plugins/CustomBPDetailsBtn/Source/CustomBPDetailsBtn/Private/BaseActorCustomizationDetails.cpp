// Fill out your copyright notice in the Description page of Project Settings.



#include "CustomBPDetailsBtn/Public/BaseActorCustomizationDetails.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "Editor/UnrealEd/Classes/Editor/EditorEngine.h"
#include "Editor/UnrealEd/Public/Editor.h"
#include "Editor/Kismet/Public/SSCSEditor.h"


struct FRestoreSelectedInstanceComponent
{
    TWeakObjectPtr<UClass> ActorClass;
    FName ActorName;
    TWeakObjectPtr<UObject> ActorOuter;

    struct FComponentKey
    {
        FName Name;
        TWeakObjectPtr<UClass> Class;

        FComponentKey(FName InName, UClass* InClass) : Name(InName), Class(InClass) {}
    };
    TArray<FComponentKey> ComponentKeys;

    FRestoreSelectedInstanceComponent()
        : ActorClass(nullptr)
        , ActorOuter(nullptr)
    { }

    void Save(AActor* InActor)
    {
        check(InActor);
        ActorClass = InActor->GetClass();
        ActorName = InActor->GetFName();
        ActorOuter = InActor->GetOuter();

        check(GEditor);
        TArray<UActorComponent*> ComponentsToSaveAndDelesect;
        for (auto Iter = GEditor->GetSelectedComponentIterator(); Iter; ++Iter)
        {
            UActorComponent* Component = CastChecked<UActorComponent>(*Iter, ECastCheckedType::NullAllowed);
            if (Component && InActor->GetInstanceComponents().Contains(Component))
            {
                ComponentsToSaveAndDelesect.Add(Component);
            }
        }

        for (UActorComponent* Component : ComponentsToSaveAndDelesect)
        {
            USelection* SelectedComponents = GEditor->GetSelectedComponents();
            if (ensure(SelectedComponents))
            {
                ComponentKeys.Add(FComponentKey(Component->GetFName(), Component->GetClass()));
                SelectedComponents->Deselect(Component);
            }
        }
    }

    void Restore()
    {
        AActor* Actor = (ActorClass.IsValid() && ActorOuter.IsValid())
            ? Cast<AActor>((UObject*)FindObjectWithOuter(ActorOuter.Get(), ActorClass.Get(), ActorName))
            : nullptr;
        if (Actor)
        {
            for (const FComponentKey& IterKey : ComponentKeys)
            {
                UActorComponent* const* ComponentPtr = Algo::FindByPredicate(Actor->GetComponents(), [&](UActorComponent* InComp)
                {
                    return InComp && (InComp->GetFName() == IterKey.Name) && (InComp->GetClass() == IterKey.Class.Get());
                });
                if (ComponentPtr && *ComponentPtr)
                {
                    check(GEditor);
                    GEditor->SelectComponent(*ComponentPtr, true, false);
                }
            }
        }
    }
};


#define LOCTEXT_NAMESPACE "FBaseActorCustomizationDetails"

TSharedRef<IDetailCustomization> FBaseActorCustomizationDetails::MakeInstance()
{
	return MakeShareable(new FBaseActorCustomizationDetails);
}

void FBaseActorCustomizationDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& EngineCategory = DetailBuilder.EditCategory("CreateWorld");

	BaseClass = DetailBuilder.GetBaseClass();
	SelectedObjectList = DetailBuilder.GetSelectedObjects();

	const FText CreateWorldBtn = LOCTEXT("CreateWorldBtn","CreateWorldBtn");
	EngineCategory.AddCustomRow(CreateWorldBtn,false)
	.NameContent()
	[
		SNullWidget::NullWidget	
	]
	.ValueContent()
	.VAlign(VAlign_Center)
	.MaxDesiredWidth(300)
	[
		SNew(SButton)
		.VAlign(VAlign_Center)
		.ToolTipText(LOCTEXT("Creating Amazing generated world","Creating Amazing generated world"))
		.OnClicked(this,&FBaseActorCustomizationDetails::ClickBtnPopulate)
		.Content()
		[
			SNew(STextBlock)
			.Text(CreateWorldBtn)
		]
	];

}

FReply FBaseActorCustomizationDetails::ClickBtnPopulate()
{
	int NumChangedProperties = 0;
	int d = 0;
	SelectedActor = Cast<AModifiedActor>(SelectedObjectList[0].Get());
    UBoxComponent* Doomy = NewObject<UBoxComponent>(SelectedActor.Get());
    SelectedActor->AddInstanceComponent(Doomy);
    FRestoreSelectedInstanceComponent RestoreSelectedInstanceComponent;
    GEditor->GetSelectedComponents()->Modify();
    SelectedActor->Modify();
    // Mark components that are either native or from the SCS as modified so they will be restored
    for (UActorComponent* ActorComponent : SelectedActor->GetComponents())
    {
        if (ActorComponent && (ActorComponent->CreationMethod == EComponentCreationMethod::SimpleConstructionScript || ActorComponent->CreationMethod == EComponentCreationMethod::Native))
        {
            ActorComponent->Modify();
        }
    }
    UBlueprint* Blueprint = Cast<UBlueprint>(SelectedActor->GetClass()->ClassGeneratedBy);
    AActor* BlueprintCDO = SelectedActor->GetClass()->GetDefaultObject<AActor>();
    const EditorUtilities::ECopyOptions::Type CopyOptions = (EditorUtilities::ECopyOptions::Type)(EditorUtilities::ECopyOptions::OnlyCopyEditOrInterpProperties | EditorUtilities::ECopyOptions::PropagateChangesToArchetypeInstances);
    NumChangedProperties = EditorUtilities::CopyActorProperties(SelectedActor.Get(), BlueprintCDO, CopyOptions);
    if (SelectedActor->GetInstanceComponents().Num() > 0)
    {
        RestoreSelectedInstanceComponent.Save(SelectedActor.Get());
        FKismetEditorUtilities::AddComponentsToBlueprint(Blueprint, SelectedActor->GetInstanceComponents());
        NumChangedProperties += SelectedActor->GetInstanceComponents().Num();
        SelectedActor->ClearInstanceComponents(true);
    }
    if (NumChangedProperties > 0)
    {
        SelectedActor = nullptr; // It is unsafe to use Actor after this point as it may have been reinstanced, so set it to null to make this obvious
    }

    FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
    FKismetEditorUtilities::CompileBlueprint(Blueprint);
    RestoreSelectedInstanceComponent.Restore();
	return FReply::Handled();
}
