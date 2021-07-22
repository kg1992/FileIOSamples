# FileIOSamples

## 빌드

윈도우즈의 경우 build.bat을 실행하면 build/debug 디렉토리에 실행파일이 생긴다.

유닉스의 경우 build.sh를 실행하면 linux 디렉토리에 실행파일이 생긴다.

프로젝트는 cmake를 사용하며, 최상위 소스 디렉토리는 src이다. 각각의 예시에 대해 하나씩 타겟이 있으며 각 타겟은 실행파일을 하나 생성한다. 빌드가 완료되고 나면 src 디렉토리의 모든 테스트용 파일을 실행파일 위치로 복사한다.

## 예시

여기에 나열된 이름은 cmake의 타겟 이름이기도 하며, 빌드 후 생성되는 실행파일의 이름이기도 하다.

1. ReadPrint

    ReadPrint.cpp

    이 예시는 텍스트 파일의 내용을 `std::string` 타입의 변수로 읽어들여 `std::cout`으로 출력한다.

    `std::ifstream`은 데이터의 파일경로를 받아 파일을 열어 `std::basic_istream`의 인터페이스를 통해 데이터를 엑세스 할 수 있게 해준다.

    `std::ifstream`은 절대경로 혹은 상대경로를 받는다. 상대경로일 경우 작업 디렉토리(Working Directory)를 기준으로 찾는다. 작업 디렉토리는 윈도우즈 콘솔에서 `echo %cd`, 리눅스 콘솔에서 `pwd`로 확인할 수 있다. 탐색기에서 더블클릭하여 exe파일을 실행한 경우 exe파일이 있는 위치가 작업 디렉토리가 된다.

    파일이 제대로 열렸는지 확인하려면 `std::ifstream::operator bool()` 캐스팅 오퍼레이터를 사용한다. 이 오퍼레이터가 반환하는 결과는 `!std::ios::fail()`을 부르는 것과 같다.

    `std::string::assign` 메소드는 두 개의 이터레이터를 받아 이터레이터가 나타내는 범위에 있는 문자열을 그대로 복사해온다. assign 메소드를 부르기 전에 원래 스트링에 있던 내용은 버려진다. 그러나 위의 예제에서는 `std::string`을 만들자마자 `std::string::assign`을 부르므로 원래부터 비어있다.

    `std::istreambuf_iterator`는 스트림 버퍼의 내용을 나타내는 이터레이터이다. 기본생성자로 생성한 경우 끝을 나타내는 용도로 쓸 수 있다.

2. ReadBinaryPrintHex

    ReadBinaryPrintHex.cpp

    이 예시는 바이너리 파일의 내용을 `std::vector` 타입의 변수로 읽어들여 `std::cout`에 출력한다.

    출력할 때 한 줄에 10 바이트 씩 출력하며, 각 바이트의 값은 16진수로 표시하고 오른쪽에 ASCII 코드 중 출력 가능한 문자가 있을 경우 표시해준다. 표시할 수 없는 문자는 `~`로 나타난다.

    ```c++
    #include <iostream>
    #include <iomanip>
    #include <fstream>
    #include <vector>
    #include <cctype>
    #include <algorithm>

    int main()
    {
        const char* const pFilename = "TextCRLF.txt";
        std::ifstream ifs(pFilename, std::ios_base::binary);
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
            std::cerr << pFilename << " was not found." << std::endl;
        }
        return 0;
    }
    ```

    `ifstream`에 `std::ios_base::binary`를 인수로 제공할 경우 파일을 바이너리로 파일로서 읽어들인다. gcc의 경우 둘 사이에 차이는 없다. VisaulC의 경우 텍스트 모드일 때 `\r\n` 문자열이 파일 속에 존재할 경우 `\r`을 무시하고 `\n`만 읽어들이며, 바이너리 모드일 경우 `\r\n`(0d0a)을 그대로 읽어들인다. 예를 들어 윈도우즈 메모장에서 작성한 파일인 `textCRLF.txt`파일로 실행 할 경우 마지막에 새줄이 들어가 있으며 파일을 실행할 때 다음과 같은 결과를 출력하며, 마지막에 0d0a가 나오는 것을 확인할 수 있다.

    ```console
              0  1  2  3  4  5  6  7  8  9
           0: 48 65 6c 6c 6f 2c 20 57 6f 72 Hello, Wor
              0  1  2  3  4  5  6  7  8  9
          10: 6c 64 21 0d 0a                ld!~~
    ```

    `<algorithm>` 헤더의 `std::transform(first_l, last_l, d_first, unary_op)` 함수는 `first_l`과 `last_l` 사이에 있는 모든 원소에 `unary_op` 함수를 불러 반환된 결과를 `d_first`에서부터 하나씩 써넣는다. `std::istreambuf_iteator<char>`는 직접 참조하면 `char`를 반환하지만 그 결과를 `std::vector<unsigned char>`에 저장하기 위해 각 원소를 캐스팅 한다.

    `unsigned char`로 저장된 데이터는 출력할 때 또다시 `unsigned int`로 캐스팅하낟. 만약 음수인 `char`를 곧바로 `unsigned int`로 캐스팅하면 `0`이 있어야 할 자리에 `f`가 와서 잘못된 결과가 출력되기 때문이다.

    ```c++
    std::cout << 'a'; // 출력: a
    std::cout << static_cast<unsigned char>('a'); // 출력: a
    std::cout << static_cast<unsigned int>('a'); // 출력: 97
    std::cout << std::hex << static_cast<unsigned int>('a'); // 출력: 61 
    std::cout << std::hex << static_cast<unsigned int>('\255'); // 출력: ffffffff
    std::cout << std::hex << static_cast<unsigned int>(static_cast<unsigned char>('\255')); // 출력: ff
    std::cout << std::hex << static_cast<unsigned int>('\255') && 0xff; // 출력: ff
    ```

    `std::transform` 함수에서 `d_first` 위치에 `std::back_inserter(data)`가 들어가는 이유는 아직 파일의 크기를 모르기 때문이다. `std::back_inserter`로 만들어진 이터레이터는 쓰기 참조만 가능하며, 내부적으로 `std::vector::push_back()`함수를 호출한다.

    소스코드의 나머지 부분은 `data`에 저장된 파일의 내용을 `std::cout`에 출력하는 부분이다.

    - // row 0, column 0 : empty  
      `std::string(size_t n, char c)` 생성자는 `c` 문자가 `n`만큼 반복되는 스트링을 만든다. 예를 들어 `std::strig(12, ' ')`를 호출하면 공백문자만 가득 찬 길이 12의 스트링이 만들어진다

    - // row 1, column 0 : second to the most significant digit index  .  
      숫자를 출력할 때 16진법으로 출력하려면 `<iomanip>`헤더의 `std::hex`를 사용한다. 다시 10진법으로 돌아가려면, `std::dec`을 사용한다.  
      출력 결과가 차지할 최소한의 너비를 지정하려면 `<iomanip>` 헤더의 `std::setw`을 사용한다. 여기서 w는 width의 약자이다.  
      지정한 너비보다 더 적게 쓰여진 경우 빈 자리는 공백 문자 ' '로 채워진다. 채워지는 문자를 바꾸려면 `std::setfill`을 사용할 수 있다.

    - // row 1, column 1 : bytes in hexadecimal display  
      `std::cout`에 출력하기 전에 `unsigned int`로 캐스팅하여 숫자로써 출력한다.  
      `std::hex`나 `std::setfill`은 `std::cout`의 플래그로 저장되며 해당 플래그는 `std::cout.flags()`메소드로 확인할 수 있다.  
      한 번 적용된 플래그는 그대로 남기 때문에 다음 출력에 영향을 미친다. 그렇기 때문에 숫자를 출력할 때 마다 항상 다시 `std::dec`, `std::hex`, `std::setfill`, `std::setw`를 다시 사용해야 한다.

    - // row 1, column 2 : bytes in string display  
      `<cctype>` 헤더의 `std::isprint`함수를 사용해 출력 가능한 ASCII 문자인지 확인할 수 있다.
