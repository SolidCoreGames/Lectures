// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BaseGameInstance.h"

void UBaseGameInstance::Init()
{
	Super::Init();

	PlayerVideoManager = NewObject<UVideoPlayerManager>(this);
	if(VideoConfig)
	{
		PlayerVideoManager->Init(VideoConfig);
		PlayerVideoManager->LoadTestVideoResources();
		PlayerVideoManager->PlayTestVideo();
	}
	

	
}
