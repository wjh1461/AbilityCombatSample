// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AbilityCombatSample : ModuleRules
{
	public AbilityCombatSample(ReadOnlyTargetRules Target) : base(Target)
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
			"AbilityCombatSample",
			"AbilityCombatSample/Variant_Platforming",
			"AbilityCombatSample/Variant_Platforming/Animation",
			"AbilityCombatSample/Variant_Combat",
			"AbilityCombatSample/Variant_Combat/AI",
			"AbilityCombatSample/Variant_Combat/Animation",
			"AbilityCombatSample/Variant_Combat/Gameplay",
			"AbilityCombatSample/Variant_Combat/Interfaces",
			"AbilityCombatSample/Variant_Combat/UI",
			"AbilityCombatSample/Variant_SideScrolling",
			"AbilityCombatSample/Variant_SideScrolling/AI",
			"AbilityCombatSample/Variant_SideScrolling/Gameplay",
			"AbilityCombatSample/Variant_SideScrolling/Interfaces",
			"AbilityCombatSample/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
