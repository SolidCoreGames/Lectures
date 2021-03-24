// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseUnitConfig.generated.h"

/**
 * 
 */

DECLARE_DELEGATE(FSimpleDel)

UCLASS(Blueprintable,BlueprintType)
class FIRSTLOOKUE_API UBaseUnitConfig : public UObject
{
	GENERATED_BODY()

	public:
	
	UBaseUnitConfig();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> UnitClass;

	UPROPERTY(EditAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	float Armor;

	UPROPERTY(EditAnywhere)
	float Damage;
	
	//DamageType
};
