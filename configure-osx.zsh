if [ -d build-osx ]
then
  rm -rf build-osx
fi
mkdir build-osx
cd build-osx || exit
cmake .. -GXcode -DCMAKE_OSX_ARCHITECTURES=x86_64 -DVCPKG_TARGET_TRIPLET=x64-osx -DCMAKE_TOOLCHAIN_FILE=/Users/hongjun/vcpkg/scripts/buildsystems/vcpkg.cmake
