// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PingPongAction.h"


void FPingPongAction::UpdateOperation(FLatentResponse& Response)
{
	TimeElapsed += Response.ElapsedTime();
	float Alpha = TimeElapsed / TotalTime;

	if(PingPongActor)
	{
		FVector NewLocation  = FMath::Lerp(StartLocation,TargetLocation,Alpha);
		PingPongActor->SetActorLocation(NewLocation);

		if(NewLocation.Equals(TargetLocation,10.0f))
		{
			FVector Temp = TargetLocation;
			TargetLocation = StartLocation;
			StartLocation = Temp;
			TimeElapsed = 0.0f;
		}
	}
	Response.FinishAndTriggerIf(bComplete || Alpha >=1.f,ExecutionFunction,OutputLink,CallbackTarget);
}
