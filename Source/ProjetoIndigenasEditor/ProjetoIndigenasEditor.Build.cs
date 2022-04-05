using UnrealBuildTool;

public class ProjetoIndigenasEditor : ModuleRules
{
    public ProjetoIndigenasEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange(new[]
        {
            "Core",
            "CoreUObject",
            "UnrealEd",
            "SlateCore",
			"Slate",
            "Toolbox",
            "PropertyEditor",
        });
        
        PrivateDependencyModuleNames.AddRange(new[] 
        {
            "ProjetoIndigenas"
        });
    }
}
