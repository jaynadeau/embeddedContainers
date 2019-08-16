#include "Pipe.h"

#include <algorithm>
#include <iterator>

#include <unistd.h>

namespace ecu {
namespace util {

Pipe::Pipe()
{
    int fdArray[2];
    if(pipe(fdArray) == -1)
    {
        // throw exception
    }
    std::copy(std::begin(fdArray), std::end(fdArray), std::begin(mDescriptors));
}

} // util
} // ecu
