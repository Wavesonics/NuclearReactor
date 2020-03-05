@echo off

if not defined ANDROID_NDK_HOME (
    echo "ANDROID_NDK_HOME is unset"
    GOTO:EOF
)

for %%a in (arm64-v8a) do (
    if not exist build\android-%%a md build\android-%%a
    cd build\android-%%a
    cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK_HOME%\build\cmake\android.toolchain.cmake -DCMAKE_MAKE_PROGRAM=%ANDROID_NDK_HOME%\prebuilt\windows-x86_64\bin\make.exe -DANDROID_PLATFORM=21 -DANDROID_ABI=%%a -DLIB_TYPE=SHARED -Wno-dev ..\..
    %ANDROID_NDK_HOME%\prebuilt\windows-x86_64\bin\make.exe
    cd ..\..
)