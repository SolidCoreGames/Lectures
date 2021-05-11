// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ZommiePawn.h"
#include "BTTask_SetZombieState.generated.h"

/**
 * 
 */
UCLASS()
class RESIDENTEVILAI_API UBTTask_SetZombieState : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EZombieState _newState = EZombieState::ZS_MoveToAttackPosition;

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
