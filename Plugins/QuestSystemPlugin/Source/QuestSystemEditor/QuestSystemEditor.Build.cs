using UnrealBuildTool;

public class QuestSystemEditor : ModuleRules
{
	public QuestSystemEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				
			}
		);
		
		PrivateIncludePaths.AddRange(new string[] { });
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"BlueprintGraph",
				"UnrealEd",
				"InputCore"
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"QuestSystemRuntime",
				"Slate",
				"SlateCore",
				"EditorStyle",
				"GraphEditor",
				"ToolMenus",
				"ApplicationCore", 
				"AITestSuite"
			}
		);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}