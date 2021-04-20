// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtr.h"
#include "GameFramework/Actor.h"
#include "Engine/LatentActionManager.h"
#include "Engine/Public/LatentActions.h"

/**
 * 
 */
class MASTERENGINE_API FPingPongAction : public FPendingLatentAction
{

 public:
 AActor* PingPongActor;

 FVector StartLocation;
 FVector TargetLocation;

 bool bComplete;

 float TimeElapsed;

 float TotalTime;

 FName ExecutionFunction;

 int32 OutputLink;

 FWeakObjectPtr CallbackTarget;

 FPingPongAction(AActor* InActor,FVector Start,FVector Target,const FLatentActionInfo& LatentInfo):PingPongActor(InActor),
 StartLocation(Start),TargetLocation(Target),bComplete(false),TimeElapsed(0.f),TotalTime(1.0f),ExecutionFunction(LatentInfo.ExecutionFunction)
 ,OutputLink(LatentInfo.Linkage),CallbackTarget(LatentInfo.CallbackTarget)
 {
 }


 virtual void UpdateOperation(FLatentResponse& Response) override;

 
};
