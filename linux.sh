# WARNING: not currently developing for linux -- this won't work

if [ ! -d "vcpkg" ]; then git clone https://github.com/Microsoft/vcpkg.git; fi
cd vcpkg

./bootstrap-vcpkg.sh -disableMetrics
./vcpkg.exe install --recurse openssl:x64-windows sqlite3:x64-windows
./vcpkg integrate install
