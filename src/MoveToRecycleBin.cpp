// MoveToRecycleBin.cpp
#include <Windows.h>
#include <shlwapi.h>
#include <tchar.h>
#include <iostream>

#pragma comment (lib, "Shlwapi.lib")

#ifdef UNICODE
#define MY_MAX_PATH 32767
#else
#define MY_MAX_PATH MAX_PATH // 260
#endif

int _tmain(int argc, TCHAR** argv)
{
    if( argc < 2 )
    {
        std::cout << "usage : MoveToRecycleBin [filename]" << std::endl;
        return 0;
    }

    TCHAR* filename = argv[1];
    TCHAR fullFilename[MY_MAX_PATH + 1] = {'\0'};
    if( PathIsRelative(filename))
    {
        GetFullPathName(
            filename, // convert this path to absolute path
            MY_MAX_PATH, // path maximum
            fullFilename, // output buffer for absolute path
            NULL // no thanks. don't output path part
        );
    }

    SHFILEOPSTRUCT f;
    ZeroMemory(&f,sizeof(SHFILEOPSTRUCT));
    f.wFunc = FO_DELETE; // delete the file
    f.fFlags = FOF_ALLOWUNDO; // don't delete permanently; move to recycle bin instead.
    f.pFrom = fullFilename; // delete 'fullFilename'. official documentation suggests that you should use absolute path for thread safty.
    int result;
    if( result = SHFileOperation(&f))
    {
        if( result == ERROR_FILE_NOT_FOUND )
        {
            std::cerr << "error: file not found." << std::endl;
        }
        else if( result == ERROR_INVALID_PARAMETER )
        {
            std::cerr << "error: invalid parameter." << std::endl;
        }
        else
        {
            std::cerr << "error: " << result << std::endl;
        }
        return result;
    }
    else if(f.fAnyOperationsAborted)
    {
        std::cout << "operation aborted. user canceled." << std::endl;
    }
    else
    {
        std::cout << "file moved to recycle bin." << std::endl;
    }
    return 0;
}
