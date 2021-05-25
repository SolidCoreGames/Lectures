// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MyWait.h"


UBTTask_MyWait::UBTTask_MyWait(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MyWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	_currTime = 0;

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_MyWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	_currTime += DeltaSeconds;
	if(_currTime >= _waitTime)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);		
	}
}
