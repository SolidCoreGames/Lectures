// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"

void AZombieAIController::BeginPlay()
{
	Super::BeginPlay();

	if(_baseBehaivourTree)
	{
		RunBehaviorTree(_baseBehaivourTree);
	}
}
