#include "System.h"

#include <cstdlib>

namespace ec {
namespace util {

System::System(const std::string& cmd, const std::string& arguments)
: mArguments{arguments},
  mCmd{cmd},
  mExitStatus{0},
  mSystemSucceeded{true}
{
    int returnValue;
    std::string cmdWithArgs{mCmd + " " + mArguments};
    returnValue = std::system(cmdWithArgs.c_str());
    if(returnValue == -1)
    {
        Error error;
        mExitStatus = error.getErrorNumber();
        mDescription = error.getErrorDescription();
        mSystemSucceeded = false;
    }
    else
    {
        // child terminated normally
        if(WIFEXITED(returnValue))
        {
            // get the exit status of the child
            mExitStatus = WEXITSTATUS(returnValue);
            mDescription = "Child terminated normally.";
            // child terminated normally but exit code indicates an error occurred in the child process
            if(mExitStatus > 0)
            {
                Error error;
                mExitStatus = error.getErrorNumber();
                mDescription = error.getErrorDescription();
            }
        }
        // child terminated by signal
        else if(WIFSIGNALED(returnValue))
        {
            // get the number of the signal that caused the child to terminate
            mExitStatus = WTERMSIG(returnValue);
            mDescription = "Signal caused child to terminate.";
        }
        // child stopped by delivery of signal
        else if(WIFSTOPPED(returnValue))
        {
            // get the number of the signal that caused the child to stop
            mExitStatus = WSTOPSIG(returnValue);
            mDescription = "Signal caused child to stop.";
        }
    }
}

SystemResult System::getResult() const
{
    return SystemResult{mExitStatus, mCmd + ": " + mDescription};
}

bool System::isSuccessful() const
{
    return mSystemSucceeded;
}

} // util
} // ec
