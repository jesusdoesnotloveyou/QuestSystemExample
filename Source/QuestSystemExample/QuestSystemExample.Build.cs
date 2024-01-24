// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class QuestSystemExample : ModuleRules
{
	public QuestSystemExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay",
			"UMG",
			"QuestSystemRuntime"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate", 
			"SlateCore"
		});
		
		PublicIncludePaths.AddRange(new string[] 
		{ 
			"QuestSystemExample/Public/Player",
			"QuestSystemExample/Public/UI",
			"QuestSystemExample/Public/QuestSystemEntities"
		}) ;
	}
}
