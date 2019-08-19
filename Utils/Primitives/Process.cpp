#include "Process.h"

#include "EcException.h"
#include "Status.h"

namespace ec {
namespace util {

Process::Process()
{
    mChildProcessId = ::fork();
    if(mChildProcessId == Status<>::SYSTEM_ERROR)
    {
        Error error;
        // throw exception
        throw EcException{error.getError()};
    }
}

bool Process::isChild() const
{
    return (mChildProcessId == 0);
}

} // util
} // ec