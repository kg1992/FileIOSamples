# file: run.sh
# author: kyunggeun lee
# brief: build FileIOSamples project
if [$1 = ""]
then
    echo usage:
    echo run [executable_name]
    goto :eof
else
    pushd ./linux
    ./$1
    popd
fi


    