// ListFolder.cpp
#include <filesystem>
#include <iostream>

int main(int argc, char** argv)
{
    if( argc < 2 )
    {
        std::cout << "usage : ListFolder [directoryName]" << std::endl;
        return 0;
    }

    std::filesystem::path path = argv[1];

    if(!std::filesystem::exists(path))
    {
        std::cerr << path << " is not found." << std::endl;
        return 1;
    }
    else if (!std::filesystem::is_directory(path))
    {
        std::cerr << path << " is not directory." << std::endl;
        return 2;
    }

    int count = 0;
    for(std::filesystem::directory_iterator iter = std::filesystem::directory_iterator(path); 
        iter != std::filesystem::directory_iterator(); 
        ++iter)
    {
        std::cout << ++count << " : " << iter->path().string() << std::endl;
    }

    return 0;
}
