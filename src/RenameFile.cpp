// RenameFile.cpp
#include <cstdio>
#include <cerrno>

int main(int argc, char** argv)
{
    if( argc < 3 )
    {
        std::puts("usage : RenameFile [source filename] [destination filename]");
        return 0;
    }

    const char* src = argv[1];
    const char* dst = argv[2];
    if( std::rename(src, dst) != 0 )
    {
        if( errno == ENOENT )
        {
            std::fprintf(stderr, "error: no entry; %s was not found.\n", src);
        }
        else if( errno == EACCES )
        {
            std::fprintf(stderr, "error: no access; process has no reading access to %s or writing access right to %s.\n", src, dst);
        }
        else if( errno == EEXIST)
        {
            std::fprintf(stderr, "error: file exists; file with name %s already exists.\n", dst);
        }
        else
        {
            std::fprintf(stderr, "error: %d.\n", errno);
        }
        return 1;
    }
    else
    {
        std::printf("renamed %s to %s.\n", src, dst);
    }
    
    return 0;
}
