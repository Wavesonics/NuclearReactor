REM Build all targets for libNuclearPhysics

REM Build for windows debug
REM call scons platform=windows target=debug

REM Build for windows release
call scons platform=windows target=release

REM Build for android
call ndk-build --jobs 12  NDK_PROJECT_PATH=.