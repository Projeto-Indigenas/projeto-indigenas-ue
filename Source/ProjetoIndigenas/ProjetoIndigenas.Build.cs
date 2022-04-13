using UnrealBuildTool;

public class ProjetoIndigenas : ModuleRules
{
	public ProjetoIndigenas(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"AIModule",
		});

		if (Target.bBuildEditor)
		{
			// PublicDependencyModuleNames.AddRange(new[]
			// {
			// 	"UnrealEd"
			// });
		}
	}
}
