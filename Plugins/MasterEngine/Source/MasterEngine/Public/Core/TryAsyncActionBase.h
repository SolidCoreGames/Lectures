// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "TryAsyncActionBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPNodeOutputPin,int32,SecondsLeft);

/**
 * 
 */
UCLASS()
class MASTERENGINE_API UTryAsyncActionBase : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	private:

	UFUNCTION()
	void InternalTick();

	UFUNCTION()
	void InternalComplete();

	static bool bActive;

	int32 SecondsLeft;

	const  UObject* WorldContext;

	FTimerHandle TimerHandler;

	public :

	UPROPERTY(BlueprintAssignable)
	FBPNodeOutputPin Tick;

	UPROPERTY(BlueprintAssignable)
	FBPNodeOutputPin Completed;

	UFUNCTION(BlueprintCallable,meta = (BlueprintInternalUseOnly="true", WorldContext = "WorldContextObject"),Category= "AsyncNode")
	static UTryAsyncActionBase* BPAsynTryTimer(const UObject* WorldContextObject,int32 Time);

	virtual void Activate() override;
	
};
