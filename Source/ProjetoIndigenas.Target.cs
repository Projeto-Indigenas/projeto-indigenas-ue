using UnrealBuildTool;

public class ProjetoIndigenasTarget : TargetRules
{
	public ProjetoIndigenasTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new[]
		{
			"ProjetoIndigenas"
		} );
	}
}
