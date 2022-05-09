using UnrealBuildTool;

public class ProjetoIndigenasEditorTarget : TargetRules
{
	public ProjetoIndigenasEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		MacPlatform.bUseDSYMFiles = false;
		IOSPlatform.bGeneratedSYM = true;
		
		ExtraModuleNames.AddRange(new[]
		{
			"ProjetoIndigenas",
			"ProjetoIndigenasEditor"
		});
	}
}
