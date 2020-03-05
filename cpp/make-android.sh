#! /bin/bash

if [ -z ${CMAKE_ANDROID_TOOLCHAIN+x} ]; then
        echo "CMAKE_ANDROID_TOOLCHAIN is unset"
        exit 1
fi

TARGETS=( armeabi-v7a arm64-v8a x86 x86_64 )

for abi in "${TARGETS[@]}"; do
        mkdir -p build/android-$abi
        cd build/android-$abi
        cmake -DCMAKE_TOOLCHAIN_FILE=$CMAKE_ANDROID_TOOLCHAIN -DANDROID_PLATFORM=21 -DANDROID_ABI=$abi -DLIB_TYPE:STRING=SHARED -Wno-dev ../..
        make
        cd ../..
done
