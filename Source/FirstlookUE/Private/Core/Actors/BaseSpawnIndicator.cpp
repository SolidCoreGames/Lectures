// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Actors/BaseSpawnIndicator.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Core/Components/BaseGravityComponent.h"
#include "Core/Actors/BaseUnit.h"
#include "Core/Actors/BaseBuilding.h"
#include "EngineUtils.h"
#include "Core/Interfaces/DamageInterface.h"

// Sets default values
ABaseSpawnIndicator::ABaseSpawnIndicator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseIndicatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseIndicatorMesh;
	SpawnHandler.BindUObject(this,&ABaseSpawnIndicator::OnUnitCreated);
}

void ABaseSpawnIndicator::PostLoad()
{
	Super::PostLoad();
}

void ABaseSpawnIndicator::PostActorCreated()
{
	Super::PostActorCreated();
	
}

// Called when the game starts or when spawned
void ABaseSpawnIndicator::BeginPlay()
{
	Super::BeginPlay();
	 UBaseGravityComponent* GravComp = NewObject<UBaseGravityComponent>(this);
	 GravComp->RegisterComponent();
	 UWorld* CurrentWorld = GetWorld();
	 // for(TActorIterator<AActor>Itr(CurrentWorld);Itr;++Itr)
	 // {
	 // 	if(Cast<ABaseBuilding>(*Itr))
	 // 	{
	 // 		ABaseBuilding* CurrentBarraks = Cast<ABaseBuilding>(*Itr);
	 // 		CurrentBarraks->OnSpawnUnit().Add(SpawnHandler);
	 // 		if(CurrentBarraks->Implements<UDamageInterface>())
	 // 		{
	 // 			UE_LOG(LogTemp,Warning,TEXT("Implements interface"));
	 // 			for (TArray<FImplementedInterface>::TConstIterator It(CurrentBarraks->GetClass()->Interfaces); It; ++It)
	 // 			{
	 // 				const UClass* InterfaceClass = It->Class;
	 // 				if (InterfaceClass && InterfaceClass->IsChildOf(UDamageInterface::StaticClass()))
	 // 				{
	 // 					UDamageInterface* listener = Cast<UDamageInterface>(InterfaceClass->GetDefaultObject());
	 // 					
	 // 					break;
	 // 				}
	 // 			}
	 // 			
	 // 		}
	 // 		//CurrentBarraks->OnSpawnUnit().Add(GravComp->OnGravityActivate);
	 // 		CurrentBarraks->OnSpawnUnit().AddLambda([](ABaseUnit* u)
	 //            {
	 //                UE_LOG(LogTemp,Warning,TEXT("I've added dynamically function to unit = %s"),*u->GetName());
	 //            });
	 // 	}
	// }
	URotatingMovementComponent* MovComp = NewObject<URotatingMovementComponent>(this);
	MovComp->RegisterComponent();
}

void ABaseSpawnIndicator::OnUnitCreated(ABaseUnit* Unit)
{
	//we need to make visual representation
	UMaterialInstanceDynamic* Mat = UMaterialInstanceDynamic::Create(IndicatorMaterial,this);
	BaseIndicatorMesh->SetMaterial(0,Mat);
	UE_LOG(LogTemp,Warning,TEXT("Unit Name is : %s"),*Unit->GetName());
}

// Called every frame
void ABaseSpawnIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

