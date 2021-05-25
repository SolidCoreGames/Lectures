// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Fire.h"
#include "AIController.h"
#include "ZommiePawn.h"

EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController * aiController = OwnerComp.GetAIOwner();

	AZommiePawn * aiPawn = Cast<AZommiePawn>(aiController->GetPawn());

	if(aiPawn)
	{
		aiPawn->Fire();
	}
	return EBTNodeResult::Type::Succeeded; 
}
