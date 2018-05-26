#include "fdistream.h"

#include <fcntl.h>
#include <unistd.h>

using namespace std;

namespace ecio {

fdistream::fdistream(const string& fileToOpen)
: begin(0),
  end(0)
{
    buffer.resize(256);
    end = &buffer.front() + buffer.size();
    fd = ::open(fileToOpen.c_str(), O_RDONLY);
    setg(reinterpret_cast<char*>(end), reinterpret_cast<char*>(end), reinterpret_cast<char*>(end));
}

streambuf::int_type fdistream::underflow()
{
    if(gptr() < egptr())
    {
        return traits_type::to_int_type(*gptr());
    }

    begin = &buffer.front();

    int numBytesRead = ::read(fd, &buffer[0], buffer.size());
    if(numBytesRead == 0)
    {
        return traits_type::eof();
    }

    setg(reinterpret_cast<char*>(buffer.front()), reinterpret_cast<char*>(buffer.front()), reinterpret_cast<char*>(buffer.front() + numBytesRead));

    return traits_type::to_int_type(*gptr());
}


}   // ecio
