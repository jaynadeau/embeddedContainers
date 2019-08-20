#ifndef PIPE_H
#define PIPE_H

#include "Descriptor.h"

#include <array>
#include <string>

namespace ec {
namespace util {

class Pipe
{
public:

    enum class PipeEnd : std::uint8_t
    {
        READ    = 0,
        WRITE   = 1,
    };

    Pipe();
    Pipe(const Pipe&) = delete;
    Pipe(Pipe&&) = delete;
    virtual ~Pipe();

    Pipe& operator=(const Pipe&) = delete;
    Pipe& operator=(Pipe&&) = delete;

    Status<std::string> read();
    Status<bool> write(const std::string& strBuffer);
    Status<bool> closeReadEnd();
    Status<bool> closeWriteEnd();

private:
    Descriptor getReadEnd() const;
    Descriptor getWriteEnd() const;

    std::array<Descriptor, 2> mDescriptors;
    bool mIsConnected;

    static constexpr std::uint32_t BUFFER_SIZE = 1024;
};

} // util
} // ec

#endif // PIPE_H
