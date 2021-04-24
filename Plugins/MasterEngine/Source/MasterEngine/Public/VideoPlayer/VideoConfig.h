// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VideoConfig.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class MASTERENGINE_API UVideoConfig : public UObject
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere)
	FString PathToVideoTexture;

	UPROPERTY(EditAnywhere)
	FString PathToMediaSource;

	UPROPERTY(EditAnywhere)
	FName TagSearchName;

	UPROPERTY(EditAnywhere)
	FVector StartPosition;

	UPROPERTY(EditAnywhere)
	FVector EndPosition;
	
};
