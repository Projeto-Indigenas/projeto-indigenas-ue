using namespace System.IO

if ([string]::IsNullOrEmpty($env:UE_ENGINE_ROOT)) {
    if ($IsMacOS) {
        $env:UE_ENGINE_ROOT = "/Users/Shared/Epic Games/UE_5.0/"
    } else {
        $env:UE_ENGINE_ROOT = "%PROGRAMFILES%/Epic Games/UE_5.0/"
    }
}

$env:PROJECT_ROOT = "$(Get-Location)"
$env:PROJECT_PATH = [Path]::Combine("$env:PROJECT_ROOT", "ProjetoIndigenas.uproject")
$env:UNREAL_BUILD_TOOL = [Path]::Combine($env:UE_ENGINE_ROOT, "Engine", "Binaries", "DotNET", "UnrealBuildTool", "UnrealBuildTool")

if ($IsWindows) {
    $env:UNREAL_BUILD_TOOL = [Path]::ChangeExtension($env:UNREAL_BUILD_TOOL, ".exe")
}

Write-Output "Using engine at: $env:UE_ENGINE_ROOT"
Write-Output "Using project at: $env:PROJECT_PATH"

function ValidateBuildTool
{
    if (![File]::Exists($unrealBuildToolPath))
    {
        Write-Error "Could not find solution generator at: $unrealBuildToolPath"

        return
    }
}

function ValidateProject 
{
    if (![File]::Exists($projectPath))
    {
        Write-Error "Could not find project at: $projectPath"

        return
    }
}