// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetZombieState.h"

#include "AIController.h"
//#include "ZommiePawn.h"

EBTNodeResult::Type UBTTask_SetZombieState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController * aiController = OwnerComp.GetAIOwner();

	AZommiePawn * aiPawn = Cast<AZommiePawn>(aiController->GetPawn());

	if(aiPawn)
	{
		aiPawn->ChangeState(_newState);
	}
	return EBTNodeResult::Type::Succeeded; 
}
