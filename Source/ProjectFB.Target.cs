// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectFBTarget : TargetRules
{
	public ProjectFBTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.AddRange(new string[] { "ProjectFB", "Widgets", "Characters","GameModes"});
		//ExtraModuleNames.Add("ProjectFB");
		//ExtraModuleNames.Add("Widgets");
		//ExtraModuleNames.Add("GameModes");
		//ExtraModuleNames.Add("Characters");
	}
}
