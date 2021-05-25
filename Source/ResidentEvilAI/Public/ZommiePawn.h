// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "ResidentEvilAI/ResidentEvilAIProjectile.h"

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

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FName _headSocketName;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAIPerceptionComponent * _perseptions;

	UPROPERTY()
	UAISenseConfig_Sight * _sightConfig;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* _gun;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* _muzzleLocation;

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<AResidentEvilAIProjectile> _projectileClass;
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	float _fireRate = 1;
	FTimerHandle _fireTimerHandle;
	bool _isRedyToFire = true;
	


public:
	// Sets default values for this pawn's properties
	AZommiePawn();

	UFUNCTION(BlueprintCallable)
	EZombieState GetCurrentState();

	UFUNCTION(BlueprintCallable)
	void ChangeState(EZombieState NewState);

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void PreseptionsUpdated(const TArray<AActor*>& Actors);
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void SetReadyToFire();

	UFUNCTION(BlueprintNativeEvent)
	void OnFreMaked();

	void OnFreMaked_Implementation();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable)
	void Fire();

};
