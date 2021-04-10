// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "IDetailCustomization.h"
#include "ModifiedActor.h"

/**
 * 
 */
 
 
 
 
class FBaseActorCustomizationDetails : public IDetailCustomization
{
	public:

	TWeakObjectPtr<UClass> BaseClass;
	TWeakObjectPtr<AActor> SelectedActor;
	TArray <TWeakObjectPtr<UObject>> SelectedObjectList;
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder )override;

	FReply ClickBtnPopulate();
};

