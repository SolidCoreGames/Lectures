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

	// Create a gun mesh component
	_gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	_gun->SetupAttachment(GetMesh(), TEXT("Weapon_Socket"));

	_muzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	_muzzleLocation->SetupAttachment(_gun);
	_muzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));


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
	//_perseptions->OnPerceptionUpdated.AddDynamic(this, &AZommiePawn::PreseptionsUpdated);
	_perseptions->OnTargetPerceptionUpdated.AddDynamic(this, &AZommiePawn::TargetPerceptionUpdated);
}

void AZommiePawn::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AResidentEvilAICharacter * plyaerCharacter = Cast<AResidentEvilAICharacter>(Actor);
	AAIController * controller = Cast<AAIController>(GetController());
	UBlackboardComponent * blackbord = controller->GetBlackboardComponent();
	if(plyaerCharacter)
	{
		if(Stimulus.IsActive())
		{
			UE_LOG(LogTemp, Warning, TEXT(" %s seen %s"), *GetName(), *Actor->GetName());
			blackbord->SetValueAsObject("TargetActor", plyaerCharacter);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT(" %s loose %s"), *GetName(), *Actor->GetName());
			blackbord->SetValueAsObject("TargetActor", nullptr);
		}
	}
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

void AZommiePawn::SetReadyToFire()
{
	_isRedyToFire = true;
}

void AZommiePawn::Fire()
{
	if(!_isRedyToFire)
		return;

	_isRedyToFire = false;
	GetWorld()->GetTimerManager().ClearTimer(_fireTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(_fireTimerHandle, this, &AZommiePawn::SetReadyToFire, _fireRate, false);
	UE_LOG(LogTemp, Warning, TEXT("Fire maked"));

	const FRotator SpawnRotation = GetControlRotation();
	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	const FVector SpawnLocation = ((_muzzleLocation != nullptr) ? _muzzleLocation->GetComponentLocation() : GetActorLocation());

	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// spawn the projectile at the muzzle
	GetWorld()->SpawnActor<AResidentEvilAIProjectile>(_projectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

}

void AZommiePawn::OnFreMaked_Implementation()
{
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

