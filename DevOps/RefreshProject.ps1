. ".\DevOps\Library.ps1"

Write-Output "Refreshing project: $env:PROJECT_PATH"
& $env:UNREAL_BUILD_TOOL -projectfiles -project="$env:PROJECT_PATH" -game -rocket -progress $args | Out-Default