// Copyright Epic Games, Inc. All Rights Reserved.


#include "Core/BaseGameModeBase.h"
#include "Engine/World.h"
#include "Core/Actors/BaseBuilding.h"
#include "EngineUtils.h"
#include "InputCoreTypes.h"
#include "Core/Actors/BaseUnit.h"
#include "Components/InputComponent.h"
#include "Engine/InputDelegateBinding.h"
#include "Engine/LocalPlayer.h"
#include "Framework/Commands/InputChord.h"
#include "Core/Controllers/BasePlayerController.h"
#include "Engine/World.h"

#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#endif
#include "GameFramework/PlayerInput.h"


ABaseGameModeBase::ABaseGameModeBase()
{
	
}


void ABaseGameModeBase::BeginPlay() 
{
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->Destroy();

	UWorld* CurrentWorld = GetWorld();
	for(TActorIterator<AActor>Itr(CurrentWorld);Itr;++Itr)
	{
		if(Cast<ABaseBuilding>(*Itr))
		{
			ABaseBuilding* CurrentBarraks = Cast<ABaseBuilding>(*Itr);
			CurrentBarraks->OnSpawnUnit().AddUObject(this,&ABaseGameModeBase::OnUnitCreated);
		}
	}
}

void ABaseGameModeBase::OnUnitCreated(ABaseUnit* Unit)
{
	ABasePlayerController* Controller = GetWorld()->SpawnActor<ABasePlayerController>();
	Controller->InputComponent = NewObject<UInputComponent>(Controller);
	if(PlayerControllerIndex == 0)
	{
		
		FInputChord Ch(EKeys::W,EInputEvent::IE_Pressed);
		Unit->AutoPossessPlayer = EAutoReceiveInput::Player0;
		Controller->AutoReceiveInput = EAutoReceiveInput::Player0;
		Controller->InitInputSystem();
		Controller->InputComponent->BindKey(Ch,EInputEvent::IE_Released,Controller,&ABasePlayerController::OnKeyPressed);
	}
	if(PlayerControllerIndex > 0)
	{
		FInputChord Ch(EKeys::Gamepad_FaceButton_Bottom,EInputEvent::IE_Pressed);
		Unit->AutoPossessPlayer = EAutoReceiveInput::Player1;
		Controller->EnableInput(Controller);
		Controller->AutoReceiveInput = EAutoReceiveInput::Player1;
		Controller->InitInputSystem();
		
		Controller->InputComponent->BindKey(Ch,EInputEvent::IE_Released,Controller,&ABasePlayerController::OnKeyPressed);
	}
	//UEditorEngine* EnginePtr = Cast<UEditorEngine>(GEngine);
	TIndirectArray<FWorldContext> GetWorldContexts = GEngine->GetWorldContexts();
	UWorld* World = GetWorldContexts.Last().World();
	FString Error;
	TArray<ULocalPlayer*> Players = World->GetGameInstance()->GetLocalPlayers();

	if(PlayerControllerIndex == 0)
	World->GetGameInstance()->RemoveLocalPlayer(Players.Last());

	
	ULocalPlayer* LocalPlayer = World ? World->GetGameInstance()->CreateLocalPlayer(PlayerControllerIndex, Error, false) : nullptr;
	LocalPlayer->SwitchController(Controller);
	Controller->InputComponent->ConditionalBuildKeyMap(Controller->PlayerInput);
	Controller->Possess(Unit);
	
	PlayerControllerIndex++;
}
