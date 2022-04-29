. ".\DevOps\Library.ps1"

[List[string]] $params = $args

foreach ($param in $params)
{
    if ($param.StartsWith("-target"))
    {
        $target = $param;
    }

    if ($param.StartsWith("-configuration"))
    {
        $configuration = $param;
    }

    if ($param.StartsWith("-platform"))
    {
        $platform = $param;
    }
}

if ([string]::IsNullOrEmpty($target))
{
    $target = "ProjetoIndigenasEditor"
}

if ([string]::IsNullOrEmpty($configuration))
{
    $configuration = "Development"
}

if ([string]::IsNullOrEmpty($platform))
{
    if ($IsMacOS)
    {
        $platform = "Mac"
    }
    else 
    {
        $platform = "Win64"
    }
}

RunBuildTool(@($target, $configuration, $platform) + $params)

if ($args.Contains("-open"))
{
    .\DevOps\OpenProject.ps1
}