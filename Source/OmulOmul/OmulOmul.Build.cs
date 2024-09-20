// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OmulOmul : ModuleRules
{
    public OmulOmul(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
            "EnhancedInput", "Json", "JsonUtilities", "HTTP", "SlateCore", "AudioCapture","SignalProcessing", "SlateCore"});
    }
}
