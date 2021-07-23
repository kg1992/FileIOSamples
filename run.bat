:: file: run.bat
:: author: kyunggeun lee
:: brief: run target executable
@echo off

pushd .\win32\Debug

echo.
echo * "echo Hello Pipe Print | PipePrint"
timeout 1 > nul
echo Hello Pipe Print | PipePrint
echo.
timeout 1 > nul

echo * "ReadPrint Text.txt"
timeout 1 > nul
ReadPrint Text.txt
echo.
timeout 1 > nul

echo * "ReadBinaryPrintHex rgbymcbw.bmp"
timeout 1 > nul
ReadBinaryPrintHex rgbymcbw.bmp
echo.
timeout 1 > nul

echo * "CopyFile Text.txt TextCopy.txt"
timeout 1 > nul
CopyFile Text.txt TextCopy.txt
echo.
timeout 1 > nul

echo * "FileEqual Text.txt TextCopy.txt"
timeout 1 > nul
FileEqual Text.txt TextCopy.txt
echo.
timeout 1 > nul

popd
