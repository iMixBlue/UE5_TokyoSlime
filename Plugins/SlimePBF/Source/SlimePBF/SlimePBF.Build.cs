using UnrealBuildTool;

public class SlimePBF : ModuleRules
{
    public SlimePBF(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",  
            "Kismet",           
            "PhysicsCore",      
            "Slate",
            "SlateCore",
            "ProceduralMeshComponent",
            "MySlime"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "RenderCore",
            "RHI"
        });

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.Add("UnrealEd");
        }
    }
}