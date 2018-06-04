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
    : fd(INVALID)
    {
        fd = ::open(filename.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
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
            std::size_t numBytesWritten = ::write(fd, &c, 1);
            if(numBytesWritten == INVALID)
            {
                // error
                return std::char_traits<char_type>::eof();
            }
        }
        return c;
    }

    virtual int_type underflow()
    {
        if (fd == INVALID)
        {
            return std::char_traits<char_type>::eof();
        }
        int_type i = std::char_traits<char_type>::eof();
        int numBytesRead = ::read(fd, &i, 1);

        if(numBytesRead <= 0)
        {
            return std::char_traits<char_type>::eof();
        }
        else
        {
            char_type c = std::char_traits<char_type>::to_char_type(i);
            setg(&c,&c,&c+1);
        }
        return i;
    }

private:
    int fd;
    static const int INVALID = -1;
};

}

#endif // UTILS_FDSTREAMBUF_H
