// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MasterEngine/Public/VideoPlayer/VideoPlayerManager.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTLOOKUE_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	public:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UVideoConfig> VideoConfig;
	
	virtual void Init() override;
	
	private:

	UPROPERTY()
	UVideoPlayerManager* PlayerVideoManager;
	
};
