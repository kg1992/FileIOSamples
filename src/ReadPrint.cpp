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
