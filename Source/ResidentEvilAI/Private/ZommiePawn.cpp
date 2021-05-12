// Fill out your copyright notice in the Description page of Project Settings.


#include "ZommiePawn.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ResidentEvilAI/ResidentEvilAICharacter.h"

// Sets default values
AZommiePawn::AZommiePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	_perseptions = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perseptions"));
	_sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));

	_perseptions->ConfigureSense(*_sightConfig);
	_perseptions->SetDominantSense(_sightConfig->GetSenseImplementation());

	_sightConfig->SightRadius = 2000;
	_sightConfig->LoseSightRadius = 2300;
	_sightConfig->PeripheralVisionAngleDegrees = 45;
	_sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	_sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	_sightConfig->DetectionByAffiliation.bDetectNeutrals = true;

}

EZombieState AZommiePawn::GetCurrentState()
{
	return _currentState;
}

void AZommiePawn::ChangeState(EZombieState NewState)
{
	_currentState = NewState;
	switch (_currentState)
	{
		case EZombieState::ZS_Patrolling:
			{
				UCharacterMovementComponent * characterMoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
				if(characterMoveComp)
				{
					characterMoveComp->MaxWalkSpeed = 100;
				}
			}
			break;
		case EZombieState::ZS_MoveToAttackPosition:
			{
				UCharacterMovementComponent * characterMoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
				if(characterMoveComp)
				{
					characterMoveComp->MaxWalkSpeed = 350;
				}
			}
			break;
		
	}
}

void AZommiePawn::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	FTransform headTransform = GetMesh()->GetSocketTransform(_headSocketName);
	OutLocation = headTransform.GetLocation();
	OutRotation = headTransform.GetRotation().Rotator();
}

// Called when the game starts or when spawned
void AZommiePawn::BeginPlay()
{
	Super::BeginPlay();
	_perseptions->OnPerceptionUpdated.AddDynamic(this, &AZommiePawn::PreseptionsUpdated);

}

void AZommiePawn::PreseptionsUpdated(const TArray<AActor*>& Actors)
{
	int32 actorsNum = Actors.Num();
	for(int32 i = 0; i < actorsNum; i++)
	{
		AResidentEvilAICharacter * plyaerCharacter = Cast<AResidentEvilAICharacter>(Actors[i]);
		if(plyaerCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT(" %s seen %s"), *GetName(), *Actors[i]->GetName());
			AAIController * controller = Cast<AAIController>(GetController());
			if(controller)
			{
				UBlackboardComponent * blackbord = controller->GetBlackboardComponent();
				if(blackbord->GetValueAsObject("TargetActor") != plyaerCharacter)
				{
					blackbord->SetValueAsObject("TargetActor", plyaerCharacter);	
				}

			}
		}
	}
}

void AZommiePawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	


}

// Called every frame
void AZommiePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZommiePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

