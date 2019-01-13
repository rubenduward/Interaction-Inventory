// Copyright 2019, KamikazeXeX. All rights reserverd.

using UnrealBuildTool;
using System.Collections.Generic;

public class JttUTarget : TargetRules
{
	public JttUTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "JttU" } );
	}
}
