// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CoreHelperLibrary.h"

ABaseGameModeBase* UCoreHelperLibrary::GetBaseGameMode()
{
    UWorld* CurrentWorld = GEngine->GetWorld();
    ABaseGameModeBase * mode = nullptr;
    if(CurrentWorld)
    {
       mode  = Cast<ABaseGameModeBase>(CurrentWorld->GetAuthGameMode());
    }
    return mode;
}
