using UnrealBuildTool;

public class ProjetoIndigenas : ModuleRules
{
	public ProjetoIndigenas(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] {"LevelSequence"});
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"AIModule",
			"DeveloperSettings",
			"UMG",
			"LevelSequence",
			"MovieScene",
			"HairStrandsCore",
			"Water",
		});
	}
}
