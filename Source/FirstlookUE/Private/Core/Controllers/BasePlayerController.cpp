// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Controllers/BasePlayerController.h"
#include "Core/Actors/BaseBuilding.h"
#include "Core/Actors/BaseUnit.h"
#include "EngineUtils.h"


void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAxis(FName("MoveForward"),this,&ABasePlayerController::OnMoveForward);
	//InputComponent->BindKey(EKeys::W,EInputEvent::IE_Pressed,this,&ABasePlayerController::OnKeyPressed);

	
}

void ABasePlayerController::OnMoveForward(float AxisValue)
{
	UE_LOG(LogTemp,Warning,TEXT("We are walking forward the current value is %s"),*FString::SanitizeFloat(AxisValue));
}

void ABasePlayerController::OnKeyPressed()
{
	UE_LOG(LogTemp,Warning,TEXT("We pressed W KEY"));
	
}