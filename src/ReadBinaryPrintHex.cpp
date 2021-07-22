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
