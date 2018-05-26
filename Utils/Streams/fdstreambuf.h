#ifndef UTILS_FDSTREAMBUF_H
#define UTILS_FDSTREAMBUF_H

#include <cstdio>
#include <fcntl.h>
#include <streambuf>
#include <string>
#include <unistd.h>

namespace ecio {

// template<typename CharT, typename Traits = std::char_traits<char_type>>
// class basic_fdstreambuf : public std::basic_streambuf<CharT, Traits>
class basic_fdstreambuf : public std::streambuf
{
public:
    basic_fdstreambuf(const std::string filename)
    {
        fd = ::open(filename.c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if(fd == INVALID)
        {
            // error
        }
    }
protected:
    virtual int_type overflow(int_type c)
    {
        if(c != std::char_traits<char_type>::eof())
        {
            std::size_t numBytesWritten = write(fd, &c, 1);
            if(numBytesWritten == INVALID)
            {
                // error
            }
            // if(putchar(c) == std::char_traits<char_type>::eof())
            // {
            //     return std::char_traits<char_type>::eof();
            // }
        }
        return c;
    }

    virtual int_type underflow()
    {

    }



private:
    int fd;
    static const int INVALID = -1;
};

}

#endif // UTILS_FDSTREAMBUF_H
