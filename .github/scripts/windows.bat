@echo off

if not exist vcpkg\vcpkg.exe ( git clone https://github.com/Microsoft/vcpkg.git )
cd vcpkg

call .\bootstrap-vcpkg.bat -disableMetrics
call .\vcpkg.exe install --recurse openssl:x64-windows sqlite3:x64-windows
call .\vcpkg.exe integrate install
echo done!
