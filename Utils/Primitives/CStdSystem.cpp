#include <util/CStdSystem.h>
#include <util/WatchDog.h>

#include <cstdlib>

namespace ec {
namespace util {

CStdSystem::CStdSystem(const std::string& cmd, const std::string& arguments, std::chrono::seconds timeout)
: mArguments{arguments},
  mCmd{cmd},
  mExitStatus{0},
  mSystemSucceeded{true}
{
    int returnValue;
    std::string cmdWithArgs{mCmd + " " + mArguments};
    WatchDog watcher{mCmd, timeout};
    returnValue = std::system(cmdWithArgs.c_str());
    watcher.cancelAndWait();
    if(returnValue == -1)
    {
        mSystemSucceeded = false;
        CStdError error;
        mExitStatus = error.getErrorNumber();
        mDescription = error.getErrorMessage();
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
                CStdError error;
                mExitStatus = error.getErrorNumber();
                mDescription = error.getErrorMessage();
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

CStdSystemResult CStdSystem::getResult() const
{
    return CStdSystemResult{mExitStatus, mCmd + ": " + mDescription};
}

bool CStdSystem::isSuccessful() const
{
    return mSystemSucceeded;
}

} // util
} // ec
