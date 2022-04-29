. ".\DevOps\Library.ps1"

[List[string]] $params = $args
RunBuildTool($params)

if ($args.Contains("-open"))
{
    .\DevOps\OpenProject.ps1
}