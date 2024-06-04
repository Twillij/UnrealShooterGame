using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealShooterServerTarget : TargetRules
{
	public UnrealShooterServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange( new string[] { "UnrealShooter" } );
	}
}
