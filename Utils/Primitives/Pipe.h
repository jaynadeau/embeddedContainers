#ifndef PIPE_H
#define PIPE_H

#include "Descriptor.h"

#include <array>

namespace ecu {
namespace util {

class Pipe
{
public:
    Pipe();
    virtual ~Pipe();
private:
    std::array<Descriptor, 2> mDescriptors;
};

} // util
} // ecu

#endif // PIPE_H
