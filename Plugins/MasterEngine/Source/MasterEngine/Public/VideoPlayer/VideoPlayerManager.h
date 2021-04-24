// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "MediaAssets/Public/MediaSource.h"
#include "MediaAssets/Public/MediaTexture.h"
#include "VideoPlayer/VideoConfig.h"

#include "VideoPlayerManager.generated.h"

/**
 * Video Player Manager responsible for playing videos in the world
 * Requirements
 * tag : VideoPlayer on Actor
 * 
 */
UCLASS()
class MASTERENGINE_API UVideoPlayerManager : public UObject
{
	GENERATED_BODY()

	public :

	DECLARE_EVENT(UVideoPlayerManager,FShowEnded)
	FShowEnded& OnShowEnded(){return _ShowEventEnded;}

	virtual void Init(TSubclassOf<UVideoConfig> VideoConfigClass);

	virtual void PlayVideo();
	
	virtual void LoadTestVideoResources();

	virtual void PlayTestVideo();

	private:

	float Alpha = 0.0f;
	
	UPROPERTY()
	UMediaPlayer * _CurrentVideoPlayer;

	UPROPERTY()
	UMediaSource* _CurrentMediaSource;

	UPROPERTY()
	UMediaTexture* _CurrentVideoTexture;

	UPROPERTY()
	UVideoConfig* _CurrentConfig;

	TWeakObjectPtr<AActor> _CurrentVideoPlayerActor;

	FTimerHandle _CurrentTimer;
	
	FShowEnded _ShowEventEnded;

	UFUNCTION()
	void FadeIn();

	bool FindAndSetVideoActor(UWorld* CurrentWorld);
	
};
