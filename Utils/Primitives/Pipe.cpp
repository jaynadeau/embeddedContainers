#include "Pipe.h"

#include <unistd.h>

namespace ecu {
namespace util {

Pipe::Pipe()
{
    int fdArray[2];
    if(pipe(fdArray))
    {
        
    }
}

} // util
} // ecu
