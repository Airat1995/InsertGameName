// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InsertGameName : ModuleRules
{
	public InsertGameName(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"PBCharacterMovement",
			"ControlFlows",
			"UMG",
			"Slate",
			"SlateCore"

		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CommonUI",
			"CommonUIEditor",
			"CommonInput"
		});
		PublicIncludePaths.AddRange(new string[]
		{
			"InsertGameName/DataAsset",
			"InsertGameName/Service",
			"InsertGameName/Service/WindowService",
			"InsertGameName/Window",
			"InsertGameName/ObjectPool"
		});
	}
}
