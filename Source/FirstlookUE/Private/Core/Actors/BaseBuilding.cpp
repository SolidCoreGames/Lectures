// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/BaseBuilding.h"
#include "Core/Actors/BaseUnit.h"
#include "UObject/Class.h"
#include "Core/Interfaces/DamageInterface.h"
#include "Core/Configs/BaseUnitConfig.h"






// Sets default values
ABaseBuilding::ABaseBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	BaseSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("BaseSpawnPoint"));
	RootComponent = RootComp;
	
	BaseMesh->SetupAttachment(RootComponent);
	BaseSpawnPoint->SetupAttachment(RootComponent);
	
}

void ABaseBuilding::SpawnUnit()
{
	ABaseUnit* SpawnedUnit = ABaseBuilding::Create_Unit(CurrentUnitConfig);
	SpawnedUnit->SetActorLocation(BaseSpawnPoint->GetComponentLocation());
	OnSpawnUnitChanged.Broadcast(SpawnedUnit);

	ABaseUnit* SpawnedUnit2 = ABaseBuilding::Create_Unit(CurrentUnitConfig);
	SpawnedUnit->SetActorLocation(BaseSpawnPoint->GetComponentLocation());
	OnSpawnUnitChanged.Broadcast(SpawnedUnit2);
}

// void ABaseBuilding::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
// {
//   Super::PostEditChangeProperty(PropertyChangedEvent);
// 	if( PropertyChangedEvent.Property )
// 	{
// 		if( PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED( ABaseBuilding, bAddInterface ) )
// 		{
// 		   FRestoreSelectedInstanceComponent RestoreSelectedInstanceComponent;
// 			UBlueprintGeneratedClass* BP_Class = Cast<UBlueprintGeneratedClass>(GetClass());
// 			UBlueprint* BP_Obj = Cast<UBlueprint>(UBlueprint::GetBlueprintFromClass(BP_Class));
// 			FBlueprintEditorUtils::ImplementNewInterface(BP_Obj, definterClass->GetFName());
//
// 			
// 			int32 NumChangedProperties = 0;
// 			// Mark components that are either native or from the SCS as modified so they will be restored
// 			for (UActorComponent* ActorComponent : this->GetComponents())
// 			{
// 				if (ActorComponent && (ActorComponent->CreationMethod == EComponentCreationMethod::SimpleConstructionScript || ActorComponent->CreationMethod == EComponentCreationMethod::Native))
// 				{
// 					ActorComponent->Modify();
// 				}
// 			}
// 			UBlueprint* Blueprint = Cast<UBlueprint>(this->GetClass()->ClassGeneratedBy);
// 			AActor* BlueprintCDO = this->GetClass()->GetDefaultObject<AActor>();
// 			const EditorUtilities::ECopyOptions::Type CopyOptions = (EditorUtilities::ECopyOptions::Type)(EditorUtilities::ECopyOptions::OnlyCopyEditOrInterpProperties | EditorUtilities::ECopyOptions::PropagateChangesToArchetypeInstances);
// 			NumChangedProperties = EditorUtilities::CopyActorProperties(this, BlueprintCDO, CopyOptions);
// 			if (this->GetInstanceComponents().Num() > 0)
// 			{
// 				RestoreSelectedInstanceComponent.Save(this);
// 				FKismetEditorUtilities::AddComponentsToBlueprint(Blueprint, this->GetInstanceComponents());
// 				NumChangedProperties += this->GetInstanceComponents().Num();
// 				this->ClearInstanceComponents(true);
// 			}
//    
// 			FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
// 			//FKismetEditorUtilities::CompileBlueprint(Blueprint);
// 			RestoreSelectedInstanceComponent.Restore();
// 		}
// 	}
// 	
// }

ABaseUnit* ABaseBuilding::Create_Unit(UBaseUnitConfig* config)
{
	UWorld* CurrentWorld  = config->GetWorld();
	ABaseUnit * Unit  = Cast<ABaseUnit>(CurrentWorld->SpawnActor(config->UnitClass));
	Unit->Init(config->Health,config->Armor,config->Damage);
	return  Unit;
}

void ABaseBuilding::OnDamageReceive()
{
	UE_LOG(LogTemp,Warning,TEXT("Damage received"));
}

// Called when the game starts or when spawned
void ABaseBuilding::BeginPlay()
{
	CurrentUnitConfig = NewObject<UBaseUnitConfig>(this,UnitConfiguration);
	Super::BeginPlay();

}

// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

