#include <iostream>
#include <fstream>

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
            if( std::istreambuf_iterator<char>(ifs).equal(std::istreambuf_iterator<char>(ifs2)) )
            {
                std::cout << "the two files are equal." << std::endl;
            }
            else
            {
                std::cout << "the two files are different" << std::endl;
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
