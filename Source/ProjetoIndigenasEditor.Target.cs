using UnrealBuildTool;

public class ProjetoIndigenasEditorTarget : TargetRules
{
	public ProjetoIndigenasEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[]
		{
			"ProjetoIndigenas",
			"ProjetoIndigenasEditor"
		});
	}
}
