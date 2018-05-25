#ifndef UTILS_FDISTREAM_H
#define UTILS_FDISTREAM_H

#include <streambuf>
#include <cstdint>
#include <string>
#include <vector>

namespace ecio
{
// input stream to read from file descriptor
class fdistream : public std::streambuf
{
public:
    fdistream() = delete;
    fdistream(const std::string& fileToOpen);
    virtual ~fdistream();

    // overflow is ignored for input
    virtual int overflow(std::uint8_t byte) { return std::char_traits<char>::eof(); }
    // underflow is implemented for input
    virtual std::streambuf::int_type underflow();
    virtual int sync();
protected:
private:
    int fd;
    std::uint8_t* begin;
    std::uint8_t* end;
    std::vector<std::uint8_t> buffer;
};

} // ecio

#endif  // UTILS_FDOSTREAM_H
