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
            else if( std::equal(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>(), std::istreambuf_iterator<char>(ifs2)) )
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
