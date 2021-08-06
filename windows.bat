cd C:/

if not exist dev\ ( mkdir dev )
cd dev

if not exist vcpkg\ ( git clone https://github.com/Microsoft/vcpkg.git )

call .\vcpkg\bootstrap-vcpkg.bat -disableMetrics

cd vcpkg

call .\vcpkg.exe install boost
call .\vcpkg.exe install cpr

call .\vcpkg.exe integrate install

echo done!