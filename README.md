# FileIOSamples

- [FileIOSamples](#fileiosamples)
  - [빌드](#빌드)
    - [윈도우즈](#윈도우즈)
    - [WSL](#wsl)
  - [예시](#예시)
    - [PipePrint](#pipeprint)
    - [ReadPrint](#readprint)
    - [ReadBinaryPrintHex](#readbinaryprinthex)
    - [CopyFile](#copyfile)
    - [FileSize](#filesize)
    - [FileEqual](#fileequal)
    - [PODToBinaryFile](#podtobinaryfile)

## 빌드

빌드 시 [CMakeLists.txt](src/CMakeLists.txt)에서 지정한 번호 이상의 cmake가 설치되어 있어야 한다. 최상위 소스 디렉토리는 [src](src/)이다. 각각의 예시에 대해 하나씩 타겟이 있으며 각 타겟은 실행파일을 하나 생성한다. 빌드가 완료되고 나면 src 디렉토리의 모든 테스트용 파일을 실행파일 위치로 복사한다.

### 윈도우즈

[build.bat](build.bat)을 실행하면 win32/debug 디렉토리에 실행파일이 생성된다.

```cmd
C:\projects\FileIOSamples> build
C:\projects\FileIOSamples> cd win32/debug
C:\projects\FileIOSamples> dir /b
```

[run.bat](run.bat)을 실행하여 각각의 실행파일을 일괄적으로 실행해보고 결과를 확인할 수 있다.

```cmd
C:\projects\FileIOSamples> run
```

### WSL

WSL에서 빌드할 수 있다.

[build.sh](build.sh)를 실행하면 linux 디렉토리에 실행파일이 생긴다.

```shell
usrname@PCNAME:/mnt/c/Projects/FileIOSamples$ ./build.sh
usrname@PCNAME:/mnt/c/Projects/FileIOSamples$ cd linux
usrname@PCNAME:/mnt/c/Projects/FileIOSamples$ ls
```

[run.sh](run.sh)를 실행하면 각각의 실행파일을 일괄적으로 실행해보고 결과를 확인할 수 있다.

```shell
usrname@PCNAME:/mnt/c/Projects/FileIOSamples$ ./run.sh
```

## 예시

여기에 나열된 이름은 cmake 타겟 이름이기도 하며, 빌드 후 생성되는 실행파일의 이름이기도 하다.

### PipePrint

이 프로그램은 `std::cin`으로 입력받는 내용을 그대로 `std::cout`으로 출력한다.

`ctrl+z`를 입력하면 중지한다.

```c++
// PipePrint.cpp
#include <iostream>
#include <algorithm>

int main()
{
    std::cout << "press ctrl+z to stop." << std::endl;
    std::copy(
        std::istreambuf_iterator<char>(std::cin), 
        std::istreambuf_iterator<char>(),
        std::ostreambuf_iterator<char>(std::cout)
        );
    return 0;
}
```

`std::copy(first, last, d_first)`는 `first` 부터 `last` 사이의 원소를 `d_first` 에서부터 차례대로 복사해 넣는 알고리즘이다.

`std::istreambuf_iterator`의 생성자는 `std::basic_istream` 객체를 받는다. 이터레이터를 참조하면 `std::basic_istream`와 연관된 스트림 객체의 `std::basic_sterambuf::sgetc` 함수를 호출해 얻은 문자를 반환한다.

`std::istreambuf_iterator::operator++`을 호출하면 내부적으로 `std::basic_sterambuf::sbumpc`를 호출해 스트림 버퍼 내에서의 위치를 한 칸 이동시킨다. `sgetc`와 `sbumpc`는 둘 다 문자를 스트림 버퍼에서 얻는 함수지만. `istream`의 `peek`과 `get`의 관계와 같이 전자는 버퍼 내에서의 위치를 옮기지 않고 후자는 버퍼 내에서의 위치를 한 칸 옮긴다.

기본생성자로 만들어진 `std::istremabuf_iterator`는 `end of stream` 이터레이터라고 하며, 끝을 지정해야 하는 곳에 대신 쓸 수 있다. `operator++`은 `sbumpc()`를 부른 결과 `eof` 문자가 반환 된 경우 자기 자신을 `end of stream` 이터레이터로 초기화 한다.

`std::ostreambuf_iterator`의 새성자는 `std::basic_ostream`객체를 받는다. 이터레이터를 참조하면 `operator=`를 정의하는 프록시 클래스를 반환한다. 프록시 클래스에 문자를 배정하면 내부적으로 `std::basic_streambuf::sputc`함수를 불러 문자를 스트림 버퍼에 하나 써넣는다.

`std::ostreambuf_iterator::operator++`은 정의되어 있지만 호출해도 위치가 실제로 바뀌지는 않고 바로 `*this`를 반환한다.

### ReadPrint

이 프로그램은 명령줄로 주어진 텍스트 파일의 내용을 `std::cout`으로 출력한다.

```c++
// ReadPrint.cpp
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
    if( argc < 2 )
    {
        std::cout << "usage : ReadPrint [filename]" << std::endl;
        return 0;
    }

    const char* const filename = argv[1];
    std::ifstream ifs(filename);
    if(ifs)
    {
        std::copy(
            std::istreambuf_iterator<char>(ifs), 
            std::istreambuf_iterator<char>(), 
            std::ostreambuf_iterator<char>(std::cout));
    }
    else
    {
        std::cerr << filename << " could not be opened for reading." << std::endl;
    }
    return 0;
}
```

`std::ifstream`은 데이터의 파일경로를 받아 파일을 열어 `std::basic_istream`의 인터페이스를 통해 데이터를 엑세스 할 수 있게 해준다.

`std::ifstream`은 절대경로 혹은 상대경로를 받는다. 상대경로일 경우 작업 디렉토리(Working Directory)를 기준으로 찾는다. 작업 디렉토리는 윈도우즈 콘솔에서 `echo %cd`, 리눅스 콘솔에서 `pwd`로 확인할 수 있다. 탐색기에서 더블클릭하여 exe파일을 실행한 경우 exe파일이 있는 위치가 작업 디렉토리가 된다.

파일이 제대로 열렸는지 확인하려면 `std::ifstream::operator bool()` 캐스팅 오퍼레이터를 사용한다. 이 오퍼레이터가 반환하는 결과는 `!std::ios::fail()`을 부르는 것과 같다.

### ReadBinaryPrintHex

이 프로그램은 명령줄 인수로 주어진 바이너리 파일의 내용을 `std::vector` 타입의 변수로 읽어들인 뒤 `std::cout`에 순서대로 출력한다.

출력할 때 한 줄에 10 바이트 씩 출력하며, 각 바이트의 값은 16진수로 표시하고 오른쪽에 ASCII 코드 중 출력 가능한 문자가 있을 경우 표시해준다. 표시할 수 없는 문자는 `~`로 나타난다.

```c++
// ReadBinaryPrintHex.cpp
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>

int main(int argc, char** argv)
{
    if( argc < 2 )
    {
        std::cout << "usage : ReadBinaryPrintHex [filename]" << std::endl;
        return 0;
    }

    const char* const filename = argv[1];
    std::ifstream ifs(filename, std::ios_base::binary);
    if(ifs)
    {
        std::vector<unsigned char> data;
        std::transform(
            std::istreambuf_iterator<char>(ifs), 
            std::istreambuf_iterator<char>(), 
            std::back_inserter(data), 
            [](char c) {return static_cast<unsigned char>(c); }
        );
        int writeCount = 0;
        const std::size_t FileSize = data.size();
        const int LineBreak = 10;
        const int Column0Size = 12;
        while(writeCount < FileSize)
        {
            char chars[LineBreak+1] = {'\0'};
            const int LineSize = std::min(FileSize - writeCount, static_cast<std::size_t>(LineBreak));
            // row 0, column 0 : empty
            std::cout << std::string(Column0Size, ' ');
            // row 0, column 1 : first digit index
            std::cout << "  0  1  2  3  4  5  6  7  8  9";
            std::cout << std::endl;
            // row 1, column 0 : second to the most significant digit index
            std::cout << std::dec << std::setfill(' ') << std::setw(Column0Size) << writeCount << ":";
            // row 1, column 1 : bytes in hexadecimal display
            for(int i = 0; i < LineSize; ++i )
            {
                const unsigned int Byte = static_cast<unsigned int>(data[writeCount]);
                chars[i] = (std::isprint(Byte) ? Byte : '~');
                std::cout << ' ' << std::hex << std::setw(2) << std::setfill('0') << Byte;
                ++writeCount;
            }
            std::cout << std::string((LineBreak - LineSize) * 3, ' ');
            // row 1, column 2 : bytes in string display
            std::cout << ' ' << chars << std::endl;
        }
    }
    else
    {
        std::cerr << filename << " could not be opened for reading." << std::endl;
    }
    return 0;
}
```

`std::ifstream`의 생성자에 `std::ios_base::binary`를 인수로 제공할 경우 파일을 바이너리로 파일로서 읽어들인다. gcc의 경우 별 차이는 없다. VisaulC의 경우 텍스트 모드일 때 `\r\n` 문자열이 파일 속에 존재할 경우 `\r`을 무시하고 `\n`만 읽어들이며, 바이너리 모드일 경우 `\r\n`(0d0a)을 그대로 읽어들인다. 예를 들어 윈도우즈 메모장에서 작성하고 저장한 파일인 `Text.txt`파일로 실행 할 경우 마지막에 새줄이 들어가 있으며 파일을 실행할 때 다음과 같은 결과를 출력한다. 마지막에 두 바이트가 0d 0a인 것을 확인할 수 있다.

```console
            0  1  2  3  4  5  6  7  8  9
        0: 48 65 6c 6c 6f 2c 20 57 6f 72 Hello, Wor
            0  1  2  3  4  5  6  7  8  9
        10: 6c 64 21 0d 0a                ld!~~
```

`<algorithm>` 헤더의 `std::transform(first_l, last_l, d_first, unary_op)` 함수는 `first_l`과 `last_l` 사이에 있는 모든 원소에 `unary_op` 함수를 불러 반환된 결과를 `d_first`에서부터 하나씩 써넣는다. `std::istreambuf_iteator<char>`는 직접 참조하면 `char`를 반환하지만 그 결과를 `std::vector<unsigned char>`에 저장하기 위해 각 원소를 캐스팅 한다.

`unsigned char`로 저장된 데이터는 출력할 때 또다시 `unsigned int`로 캐스팅한다. 만약 음수인 `char`를 곧바로 `unsigned int`로 캐스팅하면 `0`이 있어야 할 자리에 `f`가 와서 잘못된 결과가 출력되기 때문이다.

```c++
std::cout << 'a'; // 출력: a
std::cout << static_cast<unsigned char>('a'); // 출력: a
std::cout << static_cast<unsigned int>('a'); // 출력: 97
std::cout << std::hex << static_cast<unsigned int>('a'); // 출력: 61
std::cout << std::hex << static_cast<unsigned int>('\255'); // 출력: ffffffff
std::cout << std::hex << static_cast<unsigned int>(static_cast<unsigned char>('\255')); // 출력: ff
std::cout << std::hex << static_cast<unsigned int>('\255') && 0xff; // 출력: ff
```

`std::transform` 함수에서 `d_first` 위치에 `std::back_inserter(data)`가 들어가는 이유는 아직 파일의 크기를 모르기 때문이다. `std::back_inserter`로 만들어진 이터레이터는 쓰기 참조만 가능하며, 내부적으로 `std::vector::push_back`함수를 호출한다.

소스코드의 나머지 부분은 `data` 변수에 저장된 파일의 내용을 `std::cout`에 출력하는 부분이다.

- // row 0, column 0 : empty  
    `std::string(size_t n, char c)` 생성자는 `c` 문자가 `n`만큼 반복되는 스트링을 만든다. 예를 들어 `std::string(12, ' ')`를 호출하면 공백문자만 가득 찬 길이 12의 스트링이 만들어진다

- // row 1, column 0 : second to the most significant digit index  .  
    숫자를 출력할 때 16진법으로 출력하려면 `<iomanip>`헤더의 `std::hex`를 사용한다. 다시 10진법으로 돌아가려면, `std::dec`을 사용한다.  
    출력 결과가 차지할 최소한의 너비를 지정하려면 `<iomanip>` 헤더의 `std::setw`을 사용한다. 여기서 w는 width의 약자이다.  
    지정한 너비보다 더 적게 쓰여진 경우 빈 자리는 공백 문자 ' '로 채워진다. 채워지는 문자를 바꾸려면 `std::setfill`을 사용할 수 있다.

- // row 1, column 1 : bytes in hexadecimal display  
    `std::cout`에 출력하기 전에 `unsigned int`로 캐스팅하여 숫자로써 출력한다.  
    `std::hex`나 `std::setfill`은 `std::cout`의 플래그로 저장되며 해당 플래그는 `std::cout.flags()`메소드로 확인할 수 있다.  
    한 번 적용된 플래그는 출력이 끝난 후에도 그대로 남기 때문에 다음 출력에 영향을 미친다. 그렇기 때문에 숫자를 출력할 때 마다 매번 다시 `std::dec`, `std::hex`, `std::setfill`, `std::setw`를 다시 사용해야 한다.

- // row 1, column 2 : bytes in string display  
    `<cctype>` 헤더의 `std::isprint`함수를 사용해 출력 가능한 ASCII 문자인지 확인할 수 있다. 출력할 수 있는 문자의 목록은 다음과 같으며 띄어쓰기, 탭, 새 줄과 같은 공백 문자는 포함하지 않는다.

    ! " # $ % & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ? @ A B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _ ` a b c d e f g h i j k l m n o p q r s t u v w x y z { | } ~

### CopyFile

이 프로그램은 명령줄 인수로 두 개의 파일 경로를 받는다. 첫 번째 파일 경로는 복사하고 싶은 파일, 두 번째 파일 경로는 복사한 결과 생겨날 파일의 이름이다.

```c++
// CopyFile.cpp
#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
    if( argc < 3 )
    {
        std::cout << "usage : CopyFile [source filename] [destination filename]" << std::endl;
        return 0;
    }

    const char* const sourceFilename = argv[1];
    const char* const destinationFilename = argv[2];
    std::ifstream ifs(sourceFilename);
    if(ifs)
    {
        std::ofstream ofs(destinationFilename);
        if( ofs )
        {
            std::copy(
                std::istreambuf_iterator<char>(ifs),
                std::istreambuf_iterator<char>(),
                std::ostreambuf_iterator<char>(ofs)
            );
        }
        else
        {
            std::cerr << destinationFilename << " could not be opened for writing" << std::endl;
        }
    }
    else
    {
        std::cerr << sourceFilename << " could not be opened for reading." << std::endl;
    }
    return 0;
}
```

[PipePrint](#PipePrint)와 동일한 코드를 사용하지만 `std::istreambuf_iterator`, `std::ostreambuf_iterator`의 생성자에 `std::cin`과 `std::cout` 대신에 `std::ifstream`과 `std::ofsteram` 객체를 제공한다.

### FileSize

이 프로그램은 파일 이름을 명령줄 인수로 받아 파일의 크기를 여러 단위로 표시한다.

```c++
// FileSize.cpp
#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
    if( argc < 2 )
    {
        std::cout << "usage : FileSize [filename]" << std::endl;
        return 0;
    }

    const char* filename = argv[1];
    std::ifstream ifs(filename, std::ios_base::binary);
    if( ifs )
    {
        ifs.seekg(0, std::ios_base::end);
        std::streampos sizeInBytes = ifs.tellg();
        std::cout
            << "* file : " << filename << std::endl
            << "  - size in bits : " << sizeInBytes * 8 << std::endl
            << "  - size in bytes : " << sizeInBytes << std::endl
            << "  - size in kilo bytes : " << sizeInBytes / 1024.0 << std::endl
            << "  - size in mega bytes : " << sizeInBytes / (1024 * 1024.0) << std::endl
            << "  - size in giga bytes : " << sizeInBytes / (1024 * 1024 * 1024.0) << std::endl;
    }
    else
    {
        std::cerr << filename << " could not be opened for reading." << std::endl;
    }
    return 0;
}
```

`std::basic_istream::seekg` 함수는 스트림이 다음에 읽어들일 스트림 버퍼 내의 위치를 정하는 함수이다. `(0, std::ios_base::end)`를 인수로 제공할 경우 끝에서 부터 0만큼 떨어진 곳의 위치로 이동한다. 만약 이 때 `std::ifstream::get` 함수를 호출하면 `eof`를 반환한다.

`std::ifstream::tellg`는 스트림 내에서 다음에 읽을 문자의 위치를 알려준다. `eof`의 위치는 스트림의 끝이므로 그 위치가 바로 스트림의 크기를 나타낸다.

### FileEqual

이 프로그램은 두 파일을 명령줄 인수로 받아서, 두 파일의 내용이 서로 동일한지 확인한다.

```c++
// FileEqual.cpp
#include <iostream>
#include <fstream>
#include <algorithm>

int main(int argc, char** argv)
{
    if( argc < 2 )
    {
        std::cout << "usage : FileEqual [filename1] [filename2]" << std::endl;
        return 0;
    }
    
    const char* const filename1 = argv[1];
    const char* const filename2 = argv[2];
    std::ifstream ifs(filename1, std::ios_base::binary);
    if(ifs)
    {
        std::ifstream ifs2(filename2, std::ios_base::binary);
        if( ifs2 )
        {
            std::streampos size1;
            ifs.seekg(0, std::ios_base::end);
            size1 = ifs.tellg();
            ifs.seekg(0, std::ios_base::beg);

            std::streampos size2;
            ifs2.seekg(0, std::ios_base::end);
            size2 = ifs2.tellg();
            ifs2.seekg(0, std::ios_base::beg);

            if( size1 != size2 )
            {
                std::cout << "the two files are different in size." << std::endl;
            }
            else if( std::equal(
                std::istreambuf_iterator<char>(ifs),
                std::istreambuf_iterator<char>(),
                std::istreambuf_iterator<char>(ifs2))
            )
            {
                std::cout << "the two files are equal." << std::endl;
            }
            else
            {
                std::cout << "the two files are different." << std::endl;
            }
        }
        else
        {
            std::cerr << filename2 << " could not be opened for reading." << std::endl;
        }
    }
    else
    {
        std::cerr << filename1 << " could not be opened for reading." << std::endl;
    }
    return 0;
}

```

각 두 파일의 크기를 먼저 [FileSize](#FileSize) 예시에서 했던 것과 같은 방법으로 구한다. 두 파일의 크기가 서로 다른 경우 파일이 서로 다르다고 판단한다.

만약 두 파일의 크기가 서로 같다면 내용이 같은지를 확인해야 하기 때문에 `seekg(0, std::ios_base::beg)`를 호출해 각 스트림의 위치를 맨 처음 위치로 되돌린다.

`std::equal(first1, last1, first2)`는 `first1`과 `last1` 사이에 있는 원소가 `first2`에서 부터 동일하게 나타나는가 확인한다.

### PODToBinaryFile

이 프로그램은 PackedPOD.bin 파일을 만들고 구조체를 파일에 그대로 써넣는다. 그런 다음 다시 읽어들여 파일의 내용과 원래 구조체의 내용이 서로 일치하는지 확인하고 일치하면 "success.", 실패하면 "fail."을 출력한다.

```c++
// PODToBinaryFile
#include <iostream>
#include <fstream>

#pragma pack(push, 1)

struct PackedPOD
{
    int a;
    char b;
    double c;
};

#pragma pack(pop)

int main()
{
    const char* outFilename = "PackedPOD.bin";

    PackedPOD pod = {1, 'a', 3.14159};
    std::ofstream ofs(outFilename, std::ios_base::binary);
    if( ofs )
    {
        ofs.write(reinterpret_cast<const char*>(&pod), sizeof(pod));
        ofs.close();
    }
    else
    {
        std::cerr << outFilename << " could not be opened for writing.";
    }

    std::ifstream ifs(outFilename, std::ios_base::binary);
    if( ifs )
    {
        PackedPOD pod2;
        ifs.read(reinterpret_cast<char*>(&pod2), sizeof(pod2));
        
        if( !std::memcmp(&pod, &pod2, sizeof(PackedPOD)))
        {
            std::cout << "success." << std::endl;
        }
        else
        {
            std::cout << "fail." << std::endl;
        }
    }
    else
    {
        std::cerr << outFilename << " could not be opened for reading.";
    }

    return 0;
}
```

`std::ofstream::write(s, n)`은 `s`부터 시작하는 문자열을 `n`개 출력한다. 중간에 null 캐릭터가 있어도 멈추지 않으며, `n`은 정확한 배열의 크기와 쓰여질 데이터의 크기와 같다.

`std::ofstream::read(s, n)`은 스트림에서 `n`개의 바이트를 읽어 `s`에 순서대로 가져온다. 이 때에도 중간에 null 캐릭터가 있어도 멈추지 않으며, `s` 배열의 크기는 정확히 `n`이면 충분하다.

`&pod`와 같이 구조체의 주소를 얻으면 구조체의 맨 첫번째 멤버 변수의 주소를 얻는다. `reinterpret_cast`를 사용하여 구조체의 주소를 `const char*`로 캐스팅하여 단순한 바이트의 배열로 취급하고 `write` `read` 함수의 인수로 제공할 수 있다.

이러한 방식으로 데이터를 저장하는 경우를 `Unformatted I/O`라고 한다. 사용자가 읽기 어렵지만 컴퓨터가 사용하기 편한 방식으로 저장하는 것이다.

unformatted I/O를 하는 경우 컴퓨터의 구현에 따라 같은 코드에서 서로 다른 내용의 데이터가 생길 수도 있다. 예를 들어 빅 엔디안 PC에서 `int a = 1;`을 저장할 경우 `00 00 00 01`이 저장되지만 리틀 엔디안 PC에서 같은 데이터를 저장할 경우 `01 00 00 00`이 생긴다. unformatted I/O 를 사용할 경우:

1. 오직 자기 PC에서 생성한 파일 만을 사용하거나
2. 파일 형식에 따라 바이트 오더를 지정하거나 (예를 들어 BSON파일은 리틀 엔디안일 것을 권장한다)
3. 바이트 오더를 알 수 있는 힌트를 제시해야 한다 (예를 들어 UTF-16 유니코드 텍스트 문서는 BOM가 맨 처음에 온다)

`<cstring>` 헤더의 `std::memcmp(ptr1, ptr2, num)`는 주어진 `ptr1`, `ptr2`에서 시작하는 `num` 크기의 바이트 배열이 서로 일치하는지 확인한다. 일치할 경우 0을 반환한다. 서로 일치하지 않을 경우 처음으로 일치하지 않는 첫 번째 바이트의 차이(`ptr1[i] - ptr2[i]`)를 반환한다.
