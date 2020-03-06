REM [Build all targets for libNuclearPhysics]

call scons platform=windows target=release

call ndk-build --jobs 12  NDK_PROJECT_PATH=. NDK_LIBS_OUT=../bin$(TARGET_ARCH_ABI)