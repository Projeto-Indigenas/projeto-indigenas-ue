. ".\DevOps\Library.ps1"

[List[string]] $params = $args
RunBuildTool(@("-ProjectFiles") + $params)