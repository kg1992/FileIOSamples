// DeleteFile.cpp
#include <cstdio>
#include <cerrno>

int main(int argc, char** argv)
{
    if( argc < 2 )
    {
        std::puts("usage : DeleteFile [filename]");
        return 0;
    }

    const char* filename = argv[1];
    if( std::remove(filename) != 0 )
    {
        if( errno == ENOENT )
        {
            std::fprintf(stderr, "error: no entry; %s was not found.\n", filename);
        }
        else if( errno == EACCES )
        {
            std::fprintf(stderr, "error: no access; process has no writing access right to %s.\n", filename);
        }
        else
        {
            std::fprintf(stderr, "error: %d.\n", errno);
        }
        return 1;
    }
    else
    {
        std::printf("deleted %s.\n", filename);
    }

    return 0;
}
