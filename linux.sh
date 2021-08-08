echo "Directory: $PWD"

cd ~
if [ ! -d "dev" ]; then mkdir dev; fi
cd dev
if [ ! -d "vcpkg" ]; then git clone https://github.com/Microsoft/vcpkg.git; fi
cd vcpkg

./bootstrap-vcpkg.sh -disableMetrics
./vcpkg install curl
./vcpkg integrate install