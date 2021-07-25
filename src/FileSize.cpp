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
