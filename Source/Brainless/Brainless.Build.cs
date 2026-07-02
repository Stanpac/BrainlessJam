// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Brainless : ModuleRules
{
	public Brainless(ReadOnlyTargetRules Target) : base(Target)
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
			"Brainless",
			"Brainless/Variant_Platforming",
			"Brainless/Variant_Platforming/Animation",
			"Brainless/Variant_Combat",
			"Brainless/Variant_Combat/AI",
			"Brainless/Variant_Combat/Animation",
			"Brainless/Variant_Combat/Gameplay",
			"Brainless/Variant_Combat/Interfaces",
			"Brainless/Variant_Combat/UI",
			"Brainless/Variant_SideScrolling",
			"Brainless/Variant_SideScrolling/AI",
			"Brainless/Variant_SideScrolling/Gameplay",
			"Brainless/Variant_SideScrolling/Interfaces",
			"Brainless/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
