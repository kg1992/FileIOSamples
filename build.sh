# file: build.sh
# author: kyunggeun lee
# brief: build FileIOSamples project
mkdir linux
pushd linux
cmake ../src
cmake --build .
popd
