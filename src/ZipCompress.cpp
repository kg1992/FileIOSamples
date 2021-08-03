#include <iostream> 
#include <zlib.h>
#include <cassert>
#include <vector>

#define CHUNK 16654

void PrintZStream(z_stream& strm)
{
    std::cout
        << "* strm at :" << &strm << std::endl
        << "strm.avail_in == " << strm.avail_in << std::endl
        << "strm.avail_out == " << strm.avail_out << std::endl
        << "strm.next_in == " << (void*)strm.next_in << std::endl
        << "strm.next_out == " << (void*)strm.next_out << std::endl
        <<"strm.total_in == " << strm.total_in << std::endl
        << "strm.total_out == " << strm.total_out << std::endl;
}

int main()
{
    std::string str = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    std::vector<unsigned char> out_buffer(CHUNK, 0);

    int ret;
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK)
    {
        std::cerr << "deflateInit Failed" << std::endl;
        return ret;
    }

    strm.avail_in = str.size();
    strm.next_in = (Bytef*)str.data();

    strm.avail_out = out_buffer.size();
    strm.next_out = out_buffer.data();

    PrintZStream(strm);

    std::cout << "-- deflate Z_NO_FLUSH-- " << std::endl;
    while (strm.total_in != str.size())
    {
        ret = deflate(&strm, Z_NO_FLUSH);
        assert(ret != Z_STREAM_ERROR);
        PrintZStream(strm);
    }

    std::cout << "-- deflate Z_FINISH -- " << std::endl;
    ret = deflate(&strm, Z_FINISH);
    assert(ret != Z_STREAM_ERROR);
    PrintZStream(strm);

    std::cout << "-- deflate end -- " << std::endl;
    ret = deflateEnd(&strm);
    assert(ret != Z_STREAM_ERROR);
    PrintZStream(strm);

    std::vector<unsigned char> infout_buffer(CHUNK, 0);
  
    strm.avail_in = out_buffer.size();
    strm.avail_out = infout_buffer.size();
    strm.next_in = out_buffer.data();
    strm.next_out = infout_buffer.data();

    std::cout << "-- inflate init -- " << std::endl;
    ret = inflateInit(&strm);
    assert(ret != Z_STREAM_ERROR);
    PrintZStream(strm);

    std::cout << "-- inflate -- " << std::endl;
    while (strm.total_out < infout_buffer.size() && strm.total_in < out_buffer.size())
    {
        ret = inflate(&strm, Z_NO_FLUSH);
        PrintZStream(strm);
        if (ret == Z_STREAM_END) break;
        assert(ret != Z_STREAM_ERROR);
    }

    std::cout << "-- inflate end-- " << std::endl;
    ret = inflateEnd(&strm);
    assert(ret != Z_STREAM_ERROR);
    PrintZStream(strm);

    assert(std::equal(str.begin(), str.end(), infout_buffer.begin()));

    return 0;
}
