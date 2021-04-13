// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "BaseBuilding.generated.h"

class UBaseUnitConfig;
class ABaseUnit;




UCLASS()
class FIRSTLOOKUE_API ABaseBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBuilding();

	DECLARE_EVENT_OneParam(ABaseBuilding,FOnSpawnUnit,ABaseUnit*)
	FOnSpawnUnit& OnSpawnUnit()
	{
		return OnSpawnUnitChanged;		
	}
	
	UPROPERTY(EditAnywhere,Category = "Unit Config")
	TSubclassOf<UBaseUnitConfig> UnitConfiguration;

	UPROPERTY(EditAnywhere,Category = "Unit Config")
	TSubclassOf<UObject> ActionClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USceneComponent* BaseSpawnPoint;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* BaseMesh;

	UClass* definterClass;
	
	UFUNCTION(BlueprintCallable)
	void SpawnUnit();
	
	UPROPERTY(EditAnywhere,Category = "Interface Setup")
	bool bAddInterface;

	// # if WITH_EDITOR
	// virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;	
	// #endif

	
	UFUNCTION()
	static ABaseUnit* Create_Unit(UBaseUnitConfig* config);
	
protected:
	// Called when the game starts or when spawned

	UPROPERTY()
	UBaseUnitConfig* CurrentUnitConfig;

	FOnSpawnUnit OnSpawnUnitChanged;

	virtual void OnDamageReceive();
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
