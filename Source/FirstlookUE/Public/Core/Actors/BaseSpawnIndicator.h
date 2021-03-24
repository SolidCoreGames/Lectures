// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "BaseSpawnIndicator.generated.h"

class ABaseUnit;

DECLARE_DELEGATE_OneParam(FOnSpawnUnit,ABaseUnit*);

UCLASS()
class FIRSTLOOKUE_API ABaseSpawnIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSpawnIndicator();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* BaseIndicatorMesh;

	UPROPERTY(EditAnywhere)
	UMaterial* IndicatorMaterial;
	
protected:
	// Called when the game starts or when spawned
	virtual  void PostLoad() override;
	virtual void PostActorCreated() override;
	virtual void BeginPlay() override;

	FOnSpawnUnit SpawnHandler;
	
	UFUNCTION()
	void OnUnitCreated(ABaseUnit* Unit);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
