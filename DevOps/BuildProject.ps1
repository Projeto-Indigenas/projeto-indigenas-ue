. ".\DevOps\Library.ps1"

[List[string]] $params = $args

if ($params.Count -eq 0) {
    if ($IsWindows) {
        $params.Add("Win64")    
    } elseif ($IsMacOS) {
        $params.Add("Mac")
    }
}

RunBuildTool('ProjetoIndigenasEditor', 'Development', $params)