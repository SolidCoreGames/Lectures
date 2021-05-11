// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "ZommiePawn.generated.h"

UENUM(Blueprintable, BlueprintType)
enum class EZombieState: uint8
{
	ZS_Idle,
	ZS_Patrolling,
	ZS_MoveToAttackPosition,
	ZS_Attack,
	ZS_Dead
};

UCLASS()
class RESIDENTEVILAI_API AZommiePawn : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	EZombieState _currentState = EZombieState::ZS_Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAIPerceptionComponent * _perseptions;

	UPROPERTY()
	UAISenseConfig_Sight * _sightConfig;
	
public:
	// Sets default values for this pawn's properties
	AZommiePawn();

	UFUNCTION(BlueprintCallable)
	EZombieState GetCurrentState();

	UFUNCTION(BlueprintCallable)
	void ChangeState(EZombieState NewState);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void PreseptionsUpdated(const TArray<AActor*>& Actors);

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
