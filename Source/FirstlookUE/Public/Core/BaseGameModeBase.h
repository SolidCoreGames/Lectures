// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameModeBase.generated.h"


class UBaseCoreConfig;
class ABaseUnit;
/**
 * 
 */
UCLASS()
class FIRSTLOOKUE_API ABaseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	ABaseGameModeBase();


	void BeginPlay() override;

	int32 PlayerControllerIndex = 0;
	
	UFUNCTION()
    void OnUnitCreated(ABaseUnit* Unit);
};


