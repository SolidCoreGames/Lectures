// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageInterface.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnrEndActionDelegete);
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageInterface : public UInterface
{
	GENERATED_BODY()

public:
	
};

/**
 * 
 */
class FIRSTLOOKUE_API IDamageInterface
{
	GENERATED_BODY()
public:
	UFUNCTION()
       virtual void CanSave(){};
	DECLARE_EVENT(IDamageInterface,FOnSpawnUnit)
    FOnSpawnUnit& OnSpawnUnit()
	{
		return OnSpawnUnitChanged;		
	}	
	FOnSpawnUnit OnSpawnUnitChanged;

	
public:
};
