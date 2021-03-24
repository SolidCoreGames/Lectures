// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseUnit.generated.h"



UCLASS()
class FIRSTLOOKUE_API ABaseUnit : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseUnit();

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BaseSkeletalComp;


	void Init(float _Health,float _Armor,float _Damage);

	UPROPERTY(VisibleAnywhere)
	float Health;
	UPROPERTY(VisibleAnywhere)
	float Armor;
	UPROPERTY(VisibleAnywhere)
	float Damage;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
