:: file: repotest.bat
:: author: kyunggeun lee
:: brief: test by cloning, building, running the project
@echo off

echo * Cloning...
git clone https://github.com/kg1992/FileIOSamples

echo * Building..
pushd FileIOSamples
call build.bat
popd

echo * Running..
pushd FileIOSamples
echo    1. ReadPrint:
call run.bat ReadPrint
echo    2. ReadBinaryPrintHex:
call run.bat ReadBinaryPrintHex
popd

echo done
