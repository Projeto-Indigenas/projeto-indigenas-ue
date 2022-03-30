using namespace System.IO

Write-Output "Using engine at: $env:UE_ENGINE_ROOT"
$unrealBuildToolPath = [Path]::Combine($env:UE_ENGINE_ROOT, "Engine", "Binaries", "DotNET", "UnrealBuildTool.exe")
Write-Output "Using project at: $env:UE_PROJECT_ROOT"
$projectPath = [Path]::Combine("$env:UE_PROJECT_ROOT", "ProjetoIndigenas.uproject")

if (![File]::Exists($unrealBuildToolPath))
{
    Write-Error "Could not find solution generator at: $unrealBuildToolPath"

    return
}

if (![File]::Exists($projectPath))
{
    Write-Error "Could not find project at: $projectPath"

    return
}

& $unrealBuildToolPath -projectfiles -project="$projectPath" -game -rocket -progress | Out-Default