// Fill out your copyright notice in the Description page of Project Settings.


#include "ModifiedActor.h"

// Sets default values
AModifiedActor::AModifiedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AModifiedActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AModifiedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

