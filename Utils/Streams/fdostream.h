#ifndef UTILS_FDOSTREAM_H
#define UTILS_FDOSTREAM_H

#include <streambuf>
#include <cstdint>

class fdostream : public std::streambuf
{
public:
    fdostream() = delete;
    fdostream(const std::string& fileToOpen);
    virtual ~fdostream();

    // overflow is implemented for output
    virtual int overflow(std::uint8_t byte);
    // underflow is ignored for output
    virtual int underflow() { return std::char_traits<char>::eof(); }
    virtual int sync();
protected:
private:
    int fd;
    const std::uint8_t* const begin;
    const std::uint8_t* const end;
};

#endif  // UTILS_FDOSTREAM_H
