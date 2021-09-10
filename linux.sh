# WARNING: not currently developing for linux -- this won't work

if [test -f "vcpkg\vcpkg.exe"]; then
  git clone https://github.com/Microsoft/vcpkg.git
fi
cd vcpkg

sh ./bootstrap-vcpkg.sh -disableMetrics
sh ./vcpkg.exe install --recurse openssl:x64-windows sqlite3:x64-windows
sh ./vcpkg integrate install
