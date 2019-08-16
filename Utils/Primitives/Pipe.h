#ifndef PIPE_H
#define PIPE_H

#include "Descriptor.h"

#include <array>

namespace ecu {
namespace util {

class Pipe
{
public:

    enum class PipeType : std::uint8_t
    {
        READ,
        WRITE,
    };

    Pipe();
    virtual ~Pipe();

    void read();
    void write();

private:
    std::array<Descriptor, 2> mDescriptors;
};

} // util
} // ecu

#endif // PIPE_H
