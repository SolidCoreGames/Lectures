// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MasterBlueprintFunctionLibrary.generated.h"

/**
 * 
 */

UENUM()
enum EPingPongStatus
{
	Start = 0,Stop
};

UCLASS()
class MASTERENGINE_API UMasterBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public :

	/*
	 * @param InActor - actor to ping pong
	 * @param LocationA - Start Location
	 * @param LocationB - End Location
	 * @param Status - Status
	 * @param Info - Info about the Action in background
	 */

	UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", WorldContext = "WorldContextObject", ExpandEnumAsExecs = "Status"),Category = "MasterBPLibraryFunctions")
	static void PingPong(AActor* InActor, FVector LocationA,FVector LocationB,TEnumAsByte<EPingPongStatus> Status,FLatentActionInfo LatentInfo);
};
