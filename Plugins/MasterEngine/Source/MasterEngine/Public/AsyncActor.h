// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "AsyncActor.generated.h"

UCLASS()
class MASTERENGINE_API AAsyncActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsyncActor();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> MeshAssetPath;

	UPROPERTY()
	UStaticMeshComponent* MeshComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TSharedPtr<FStreamableHandle> AssetHandle;
	FStreamableDelegate OnContentReady;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void LoadAsync();

	UFUNCTION()
	void OnContentLoadCallback();

};
