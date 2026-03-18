// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MySlime : ModuleRules
{
	public MySlime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MySlime",
			"MySlime/Variant_Platforming",
			"MySlime/Variant_Platforming/Animation",
			"MySlime/Variant_Combat",
			"MySlime/Variant_Combat/AI",
			"MySlime/Variant_Combat/Animation",
			"MySlime/Variant_Combat/Gameplay",
			"MySlime/Variant_Combat/Interfaces",
			"MySlime/Variant_Combat/UI",
			"MySlime/Variant_SideScrolling",
			"MySlime/Variant_SideScrolling/AI",
			"MySlime/Variant_SideScrolling/Gameplay",
			"MySlime/Variant_SideScrolling/Interfaces",
			"MySlime/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
