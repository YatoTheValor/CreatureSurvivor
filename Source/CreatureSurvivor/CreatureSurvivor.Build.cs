// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CreatureSurvivor : ModuleRules
{
	public CreatureSurvivor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CreatureSurvivor",
			"CreatureSurvivor/Variant_Strategy",
			"CreatureSurvivor/Variant_Strategy/UI",
			"CreatureSurvivor/Variant_TwinStick",
			"CreatureSurvivor/Variant_TwinStick/AI",
			"CreatureSurvivor/Variant_TwinStick/Gameplay",
			"CreatureSurvivor/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
