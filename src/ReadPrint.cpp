#include <iostream>
#include <fstream>
#include <string>

int main()
{
    const char* const pFilename = "TextCRLF.txt";
    std::ifstream ifs(pFilename);
    if(ifs)
    {
        std::string str;
        str.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
        std::cout << str;
    }
    else
    {
        std::cerr << pFilename << " was not found." << std::endl;
    }
    return 0;
}
