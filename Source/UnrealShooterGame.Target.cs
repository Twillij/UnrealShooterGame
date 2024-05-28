using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealShooterGameTarget : TargetRules
{
	public UnrealShooterGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange( new string[] { "UnrealShooterGame" } );
	}
}
