. ".\DevOps\Library.ps1"

if ($IsWindows) {
    Start-Process "$env:PROJECT_PATH"
} else {
    open "$env:PROJECT_PATH"
}