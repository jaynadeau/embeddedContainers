#include "Pipe.h"

#include "EcException.h"

#include <algorithm>
#include <iterator>

#include <unistd.h>

namespace ec {
namespace util {

Pipe::Pipe()
: mIsConnected(false)
{
    int fdArray[2];
    if(pipe(fdArray) == Status<>::SYSTEM_ERROR)
    {
        Error error;
        // throw exception
        throw EcException{error.getError()};
    }
    std::copy(std::begin(fdArray), std::end(fdArray), std::begin(mDescriptors));
    mIsConnected = true;
}

Status<std::string> Pipe::read()
{
    Status<std::string> status;
    std::string strBuffer;
    if(mIsConnected)
    {
        char buffer[BUFFER_SIZE];
        if(::read(getReadEnd().getDescriptor(), buffer, BUFFER_SIZE) == Status<>::SYSTEM_ERROR)
        {
            status.createError();
        }
        else
        {
            strBuffer = buffer;
            status.createSuccess(strBuffer);
        }
    }
    return status;
}

Status<bool> Pipe::write(const std::string& strBuffer)
{
    Status<bool> status{true};
    if(mIsConnected)
    {
        if(::write(getWriteEnd().getDescriptor(), strBuffer.c_str(), strBuffer.size()) == Status<>::SYSTEM_ERROR)
        {
            status.createError();
        }
    }
    return status;
}

Status<bool> Pipe::closeReadEnd()
{
    return getReadEnd().close();
}

Status<bool> Pipe::closeWriteEnd()
{
    return getWriteEnd().close();
}

Descriptor Pipe::getReadEnd() const
{
    return mDescriptors.at(static_cast<unsigned long>(PipeEnd::READ));
}

Descriptor Pipe::getWriteEnd() const
{
    return mDescriptors.at(static_cast<unsigned long>(PipeEnd::WRITE));
}

} // util
} // ec
