// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ResidentEvilAIHUD.generated.h"

UCLASS()
class AResidentEvilAIHUD : public AHUD
{
	GENERATED_BODY()

public:
	AResidentEvilAIHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

