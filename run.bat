:: file: run.bat
:: author: kyunggeun lee
:: brief: run target executable
@echo off

pushd .\win32\Debug

echo.
echo "echo Hello Pipe Print | PipePrint"
timeout 1 > nul
echo Hello Pipe Print | PipePrint
echo.
timeout 1 > nul

echo "ReadPrint Text.txt"
timeout 1 > nul
ReadPrint Text.txt
echo.
timeout 1 > nul

echo "ReadBinaryPrintHex rgbymcbw.bmp"
timeout 1 > nul
ReadBinaryPrintHex rgbymcbw.bmp
echo.
timeout 1 > nul

echo "CopyFile Text.txt TextCopy.txt"
timeout 1 > nul
CopyFile Text.txt TextCopy.txt
echo.
timeout 1 > nul

echo "FileSize rgbymcbw.bmp"
timeout 1 > nul
FileSize rgbymcbw.bmp
echo.
timeout 1 > nul

echo "FileEqual Text.txt TextCopy.txt"
timeout 1 > nul
FileEqual Text.txt TextCopy.txt
echo.
timeout 1 > nul

echo "FileEqual Text.txt rgbymcbw.bmp"
timeout 1 > nul
FileEqual Text.txt rgbymcbw.bmp
echo.
timeout 1 > nul

echo "FileEqual Text.txt TextSimilar.txt"
timeout 1 > nul
FileEqual Text.txt TextSimilar.txt
echo.
timeout 1 > nul

echo "PODToBinaryFile"
timeout 1 > nul
PODToBinaryFile
echo.
timeout 1 > nul

echo "type BookCommands.txt | Book"
timeout 1 > nul
type BookCommands.txt | Book
echo.
timeout 1 > nul

echo "DeleteFile DeleteMe.txt"
timeout 1 > nul
DeleteFile aaaa
echo.
timeout 1 > nul

echo "echo delete me! > DeleteMe.txt"
echo "DeleteFile TextCopy.txt"
timeout 1 > nul
echo delete me! > DeleteMe.txt
DeleteFile DeleteMe.txt
echo.
timeout 1 > nul

echo "MoveToRecycleBin DeleteMe.txt"
timeout 1 > nul
MoveToRecycleBinA DeleteMe.txt
echo.
timeout 1 > nul

echo "echo delete me! > DeleteMe.txt"
echo "MoveToRecycleBin DeleteMe.txt"
timeout 1 > nul
echo delete me! > DeleteMe.txt
MoveToRecycleBinA DeleteMe.txt
echo.
timeout 1 > nul

echo "echo rename me! > RenameMe.txt"
echo "RenameFile RenameMe.txt Renamed.txt"
timeout 1 > nul
echo rename me! > RenameMe.txt
RenameFile RenameMe.txt Renamed.txt
echo.
timeout 1 > nul

popd
