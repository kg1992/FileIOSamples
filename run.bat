:: file: run.bat
:: author: kyunggeun lee
:: brief: build FileIOSamples project
@echo off

if "%1"=="" (
    echo usage:
    echo run [executable_name]
    goto :eof
) else (
    pushd .\build\Debug
    %1.exe
    popd
)


    