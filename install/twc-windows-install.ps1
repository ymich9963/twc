$TWC_install_path = 'C:\Program Files\twc'
$TWC_exe_link = "https://github.com/ymich9963/twc/releases/download/v1.1.1/twc.exe"

if (Test-Path -Path $TWC_install_path) {
    Write-Output "Removing previously installed executable."
    Remove-Item $TWC_install_path -r # rm command
}

mkdir $TWC_install_path 
curl -fsSLO $TWC_exe_link
Move-Item twc.exe $TWC_install_path # mv command
Write-Output "Downloaded executable." # echo command

$Sys_Env_Path_Value = Get-ItemProperty -Path 'HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Environment\' -Name Path 

# Change the backslashes to frontslashes so that -split can work
$TWC_install_path_frontslash = $TWC_install_path -replace "\\","/"
$Sys_Env_Path_Value_frontslash = $Sys_Env_Path_Value.Path -replace "\\", "/"

# Check if the install path exists by splitting the Path variable value
$TWC_path_check = $Sys_Env_Path_Value_frontslash -split $TWC_install_path_frontslash | Measure-Object 

if ($TWC_path_check.Count -igt 1) {
    Write-Output "Detected previous TWC installation."
    Write-Output "Nothing was added to the system Path variable."
} else {
    Write-Output "Detected no previous TWC install."
    Write-Output "Adding executable to system Path environment variable."
    $New_Path_Value = $Sys_Env_Path_Value.Path + ";" + $TWC_install_path + ";" 
    Set-ItemProperty -Path 'HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Environment\' -Name Path -Value $New_Path_Value # set the system environment variable for the TWC
}

Write-Output "Succesfully installed TWC."

Read-Host -Prompt "Press Enter to exit"

Exit

