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
				// Seems like FEditorStyle from EditorStyle gonna be deprecated in UE5, gotta use FAppStyle from SlateCore module
				"EditorStyle",
				"GraphEditor",
				"ToolMenus",
				"ApplicationCore", 
				"AssetTools",
				// Probably can be removed
				"AITestSuite",
				// For WorkflowTabFactory
				"Kismet",
			}
		);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}