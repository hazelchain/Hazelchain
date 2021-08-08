@REM @echo off

echo "Directory: %~f0"

cd C:/

if not exist dev\ ( mkdir dev )
cd dev
if not exist vcpkg\vcpkg.exe ( git clone https://github.com/Microsoft/vcpkg.git )

call :GETPARENT PARENT
if /I "%PARENT%" == "powershell" goto :POWERSHELL
if /I "%PARENT%" == "pwsh" goto :POWERSHELL

cd vcpkg
call bootstrap-vcpkg.bat -disableMetrics
call vcpkg.exe install boost:x64-windows
call vcpkg.exe install cpr:x64-windows
call vcpkg.exe integrate install
echo done!
goto :EOF

:POWERSHELL
cd vcpkg
call .\bootstrap-vcpkg.bat -disableMetrics
call .\vcpkg.exe install boost:x64-windows
call .\vcpkg.exe install cpr:x64-windows
call .\vcpkg.exe integrate install
echo done!
goto :EOF

:GETPARENT
SET "PSCMD=$ppid=$pid;while($i++ -lt 3 -and ($ppid=(Get-CimInstance Win32_Process -Filter ('ProcessID='+$ppid)).ParentProcessId)) {}; (Get-Process -EA Ignore -ID $ppid).Name"
for /f "tokens=*" %%i in ('powershell -noprofile -command "%PSCMD%"') do SET %1=%%i
