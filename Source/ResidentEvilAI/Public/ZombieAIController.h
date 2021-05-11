// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class RESIDENTEVILAI_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Behaivour")
	UBehaviorTree * _baseBehaivourTree;

public:
	virtual void BeginPlay() override;
};
