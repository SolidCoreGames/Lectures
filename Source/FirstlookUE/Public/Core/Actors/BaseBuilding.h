// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#if WITH_EDITOR
#include "Kismet2/BlueprintEditorUtils.h"
#include "Editor/UnrealEd/Public/Kismet2/KismetEditorUtilities.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Editor/UnrealEd/Classes/Editor/EditorEngine.h"
#include "Editor/Kismet/Public/SSCSEditor.h"
#include "Editor/UnrealEd/Public/Editor.h"
#include "Engine/Selection.h"
#endif

#include "BaseBuilding.generated.h"

class UBaseUnitConfig;
class ABaseUnit;

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


UCLASS()
class FIRSTLOOKUE_API ABaseBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBuilding();

	DECLARE_EVENT_OneParam(ABaseBuilding,FOnSpawnUnit,ABaseUnit*)
	FOnSpawnUnit& OnSpawnUnit()
	{
		return OnSpawnUnitChanged;		
	}
	
	UPROPERTY(EditAnywhere,Category = "Unit Config")
	TSubclassOf<UBaseUnitConfig> UnitConfiguration;

	UPROPERTY(EditAnywhere,Category = "Unit Config")
	TSubclassOf<UObject> ActionClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USceneComponent* BaseSpawnPoint;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* BaseMesh;

	UClass* definterClass;
	
	UFUNCTION(BlueprintCallable)
	void SpawnUnit();
	
	UPROPERTY(EditAnywhere,Category = "Interface Setup")
	bool bAddInterface;

	// # if WITH_EDITOR
	// virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;	
	// #endif

	
	UFUNCTION()
	static ABaseUnit* Create_Unit(UBaseUnitConfig* config);
	
protected:
	// Called when the game starts or when spawned

	UPROPERTY()
	UBaseUnitConfig* CurrentUnitConfig;

	FOnSpawnUnit OnSpawnUnitChanged;

	virtual void OnDamageReceive();
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
