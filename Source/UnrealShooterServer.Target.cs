using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealShooterServerTarget : TargetRules
{
	public UnrealShooterServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange( new string[] { "UnrealShooter" } );
	}
}
