using namespace System.IO
using namespace System.Collections.Generic

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

function RunBuildTool([Array] $params)
{
    $unrealBuildScript = ""
    
    if ($IsWindows) {
        $unrealBuildScript = [Path]::Combine($env:UE_ENGINE_ROOT, "Engine", "Build", "BatchFiles", "Build.bat")
    } else {
        $unrealBuildScript = [Path]::Combine($env:UE_ENGINE_ROOT, "Engine", "Build", "BatchFiles", "Mac", "Build.sh")
    }

    & "$unrealBuildScript" `
        -Project="$env:PROJECT_PATH" `
        -WaitMutex `
        -FromMsBuild `
        $params | Out-Default
}

function RunAutomationTool([Array] $params)
{
    $unrealAutomationTool = ""
    if ($IsWindows) {
        $unrealAutomationTool = [Path]::Combine($env:UE_ENGINE_ROOT, "Engine", "Build", "BatchFiles", "RunUAT.bat")
    } else {
        $unrealAutomationTool = [Path]::Combine($env:UE_ENGINE_ROOT, "Engine", "Build", "BatchFiles", "RunUAT.sh")
    }
    
    & "$unrealAutomationTool" `
        BuildCookRun `
        -project="$env:PROJECT_PATH" `
        -noP4 `
        -cook `
        -allmaps `
        -build `
        -stage `
        -pak `
        -archive `
        $params | Out-Default
}