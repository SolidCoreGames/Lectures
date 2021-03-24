// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseGravityComponent.generated.h"

class ABaseUnit;

DECLARE_DELEGATE_OneParam(FOnActivateGravity,ABaseUnit*);

UCLASS(Blueprintable,BlueprintType,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTLOOKUE_API USomeGravityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USomeGravityComponent();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bEnableGravity;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DeltaGravityMulitplier;

	FOnActivateGravity OnGravityActivate;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* RootActor;

	void GravityActivate(ABaseUnit* unitThatActivateGravity);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

UCLASS(Blueprintable,BlueprintType,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTLOOKUE_API UBaseGravityComponent : public USomeGravityComponent
{GENERATED_BODY()};
