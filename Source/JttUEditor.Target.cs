// Copyright 2019, KamikazeXeX. All rights reserverd.

using UnrealBuildTool;
using System.Collections.Generic;

public class JttUEditorTarget : TargetRules
{
	public JttUEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "JttU" } );
	}
}
