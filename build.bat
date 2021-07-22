:: file: build.bat
:: author: kyunggeun lee
:: brief: build FileIOSamples project
@echo off

mkdir win32
pushd win32
cmake ../src
cmake --build .
popd
    