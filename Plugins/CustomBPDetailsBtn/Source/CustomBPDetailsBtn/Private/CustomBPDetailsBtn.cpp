// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomBPDetailsBtn.h"


#include "CustomBPDetailsBtn/Public/BaseActorCustomizationDetails.h"
#include "CustomBPDetailsBtn/Public/ModifiedActor.h"

#define LOCTEXT_NAMESPACE "FCustomBPDetailsBtnModule"

void FCustomBPDetailsBtnModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(AModifiedActor::StaticClass()->GetFName()
		,FOnGetDetailCustomizationInstance::CreateStatic(&FBaseActorCustomizationDetails::MakeInstance));
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FCustomBPDetailsBtnModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomBPDetailsBtnModule, CustomBPDetailsBtn)