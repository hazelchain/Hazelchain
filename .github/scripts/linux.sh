# WARNING: not currently developing for linux -- this won't work
cd ../../

if [test -f "vcpkg\vcpkg.exe"]; then
  git clone https://github.com/Microsoft/vcpkg.git
fi

sh ./vcpkg/bootstrap-vcpkg.sh -disableMetrics
sh ./vcpkg/vcpkg install --recurse openssl:x64-windows sqlite3:x64-windows
sh ./vcpkg/ vcpkg integrate install
