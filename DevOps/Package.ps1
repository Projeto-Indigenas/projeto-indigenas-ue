. ".\DevOps\Library.ps1"

[List[string]] $params = $args
if ($params.Count -eq 0) {
    if ($IsWindows) {
        $params.Add("-platform=Win64")        
    } else {
        $params.Add("-platform=Mac")
    }
}

if ($params.ToString().Contains("-clientconfig") -eq $false) {
    $params.Add("-clientconfig=Development")
}

RunAutomationTool($params)