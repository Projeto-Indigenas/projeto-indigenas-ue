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
            "PropertyEditor", 
            "EditorFramework",
            "Blutility",
            "UMG",
            "UMGEditor",
            "InputCore",
        });
        
        PrivateDependencyModuleNames.AddRange(new[] 
        {
            "ProjetoIndigenas"
        });
    }
}
