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
