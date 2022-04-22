using UnrealBuildTool;

public class ProjetoIndigenasTarget : TargetRules
{
	public ProjetoIndigenasTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		MacPlatform.bUseDSYMFiles = false;
		IOSPlatform.bGeneratedSYM = true;
		
		ExtraModuleNames.AddRange( new[]
		{
			"ProjetoIndigenas"
		} );
	}
}
