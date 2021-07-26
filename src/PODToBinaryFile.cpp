// PODToBinaryFile
#include <iostream>
#include <fstream>
#include <cstring>

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