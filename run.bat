:: file: run.bat
:: author: kyunggeun lee
:: brief: run target executable
@echo off

if "%1"=="" (
    echo usage:
    echo run [executable_name]
    goto :eof
) else (
    pushd .\win32\Debug
    %1.exe
    popd
)
