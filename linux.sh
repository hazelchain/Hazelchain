cd ~

if [ ! -d "dev" ]; then mkdir dev; fi
cd dev

if [ ! -d "vcpkg" ]; then git clone https://github.com/Microsoft/vcpkg.git; fi

./vcpkg/bootstrap-vcpkg.sh

./vcpkg install boost-multiprecision
./vcpkg install cpr
