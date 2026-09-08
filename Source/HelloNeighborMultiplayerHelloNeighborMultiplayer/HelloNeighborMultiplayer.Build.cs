using UnrealBuildTool;

public class HelloNeighborMultiplayer : ModuleRules
{
	public HelloNeighborMultiplayer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencies.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Networking",
				"OnlineSubsystem",
				"OnlineSubsystemUtils",
			}
		);

		PrivateDependencies.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
		);
	}
}
