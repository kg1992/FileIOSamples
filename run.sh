# file: run.sh
# author: kyunggeun lee
# brief: run target executables
pushd linux

echo
echo "echo Hello Pipe Print | PipePrint"
sleep 1
echo Hello Pipe Print | ./PipePrint
echo
sleep 1

echo "ReadPrint Text.txt"
sleep 1
./ReadPrint Text.txt
echo
sleep 1

echo "ReadBinaryPrintHex rgbymcbw.bmp"
sleep 1
./ReadBinaryPrintHex rgbymcbw.bmp
echo
sleep 1

echo "CopyFile Text.txt TextCopy.txt"
sleep 1
./CopyFile Text.txt TextCopy.txt
echo
sleep 1

echo "FileSize rgbymcbw.bmp"
sleep 1
./FileSize rgbymcbw.bmp
echo
sleep 1

echo "FileEqual Text.txt TextCopy.txt"
sleep 1
./FileEqual Text.txt TextCopy.txt
echo
sleep 1

echo "FileEqual Text.txt rgbymcbw.bmp"
sleep 1
./FileEqual Text.txt rgbymcbw.bmp
echo
sleep 1

echo "FileEqual Text.txt TextSimilar.txt"
sleep 1
./FileEqual Text.txt TextSimilar.txt
echo
sleep 1

echo "PODToBinaryFile"
sleep 1
./PODToBinaryFile
echo
sleep 1

echo "type BookCommands.txt | Book"
sleep 1
cat BookCommands.txt | ./Book
echo
sleep 1

echo "DeleteFile DeleteMe.txt"
sleep 1
./DeleteFile aaaa
echo
sleep 1

echo "echo delete me! > DeleteMe.txt"
echo "DeleteFile TextCopy.txt"
sleep 1
echo delete me! > DeleteMe.txt
./DeleteFile DeleteMe.txt
echo
sleep 1

echo "echo rename me! > RenameMe.txt"
echo "RenameFile RenameMe.txt Renamed.txt"
sleep 1
echo rename me! > RenameMe.txt
./RenameFile RenameMe.txt Renamed.txt
echo
sleep 1

popd
