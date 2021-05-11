// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ResidentEvilAI : ModuleRules
{
	public ResidentEvilAI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "GameplayTasks" });
	}
}
