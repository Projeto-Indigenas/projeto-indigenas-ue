. ".\DevOps\Library.ps1"

Write-Output "Building project: $env:PROJECT_PATH"
$unrealBuildBat = [Path]::Combine($env:UE_ENGINE_ROOT, "Engine", "Build", "BatchFiles", "Build.bat")
& $unrealBuildBat `
    ProjetoIndigenasEditor `
    Win64 `
    Development `
    -Project="$env:PROJECT_PATH" `
    -WaitMutex `
    -FromMsBuild | Out-Default