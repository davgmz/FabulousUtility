using UnrealBuildTool;

public class FabulousAbilitySystem : ModuleRules
{
	public FabulousAbilitySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;

		bEnableNonInlinedGenCppWarnings = true;

		PrivateDependencyModuleNames.AddRange(new[] {"Core", "CoreUObject", "Engine"});
	}
}