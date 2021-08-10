# WARNING: not currently developing for linux -- this won't work

echo "Directory: $PWD"

cd ~
if [ ! -d "dev" ]; then mkdir dev; fi
cd dev
if [ ! -d "vcpkg" ]; then git clone https://github.com/Microsoft/vcpkg.git; fi
cd vcpkg

./bootstrap-vcpkg.sh -disableMetrics
call .\vcpkg.exe install openssl
./vcpkg integrate install