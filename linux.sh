echo "Directory: $PWD"

cd ~

if [ ! -d "dev" ]; then mkdir dev; fi
cd dev

if [ ! -d "vcpkg" ]; then git clone https://github.com/Microsoft/vcpkg.git; fi
cd vcpkg

./bootstrap-vcpkg.sh
./vcpkg install boost:x64-linux
./vcpkg install cpr:x64-linux
./vcpkg integrate install