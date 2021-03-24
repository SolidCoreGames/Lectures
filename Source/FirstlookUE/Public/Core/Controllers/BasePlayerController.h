// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTLOOKUE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void  OnMoveForward(float AxisValue);

	UFUNCTION()
	void OnKeyPressed();

};
