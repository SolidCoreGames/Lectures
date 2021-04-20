// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TryAsyncActionBase.h"

bool UTryAsyncActionBase::bActive = false;

void UTryAsyncActionBase::InternalTick()
{
	SecondsLeft -= 1;
	Tick.Broadcast(SecondsLeft);
	if(SecondsLeft <= 0)
	{
		InternalComplete();	
	}
}

void UTryAsyncActionBase::InternalComplete()
{
	if(WorldContext)
	{
		WorldContext->GetWorld()->GetTimerManager().ClearTimer(TimerHandler);
		TimerHandler.Invalidate();
		Completed.Broadcast(SecondsLeft);
		UTryAsyncActionBase::bActive = false;
	}
}

UTryAsyncActionBase* UTryAsyncActionBase::BPAsynTryTimer(const UObject* WorldContextObject, int32 Time)
{
	UTryAsyncActionBase* Node = NewObject<UTryAsyncActionBase>();
	if(Node)
	{
		Node->WorldContext = WorldContextObject;
		Node->SecondsLeft = Time;
		return Node;
	}
	return nullptr;
}

void UTryAsyncActionBase::Activate()
{
	if(UTryAsyncActionBase::bActive)
	{
		FFrame::KismetExecutionMessage(TEXT("Async action is already running"),ELogVerbosity::Warning);
		return;
	}
	FFrame::KismetExecutionMessage(TEXT("Async action started"),ELogVerbosity::Log);

	if(WorldContext)
	{
		UTryAsyncActionBase::bActive = true;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUObject(this,&UTryAsyncActionBase::InternalTick);
		WorldContext->GetWorld()->GetTimerManager().SetTimer(TimerHandler,TimerDelegate,1.0f,true);
	}
	
}
