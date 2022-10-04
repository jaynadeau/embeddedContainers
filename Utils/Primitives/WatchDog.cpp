#include <WatchDog.h>

#include <CStdError.h>

#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <stdexcept>

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

namespace util {

WatchDog::WatchDog(const std::string& processToWatch, std::chrono::seconds timeout)
:   mProcessToWatch{processToWatch},
    mTimeout{timeout}
{
    // if timeout is 0 seconds, then wait forever on process and do nothing in watchdog
    if(mTimeout != std::chrono::seconds(0))
    {
        mTimeoutThread = std::thread{
            [this](std::chrono::seconds timeout, const std::string& processToWatch) {
                try
                {
                    std::unique_lock<std::mutex> lock(mMx);
                    // if predicate is still false, then we have timed out, kill the process 
                    if(!mCv.wait_for(lock, timeout, [this]{return mCancelWatch;}))
                    {
                        // kill process after timeout
                        convertProcessNameToPid();
                        for(const auto& process : mProcesses)
                        {
                            int processId = process.getPid();
                            if(processId != -1)
                            {
                                if(::kill(processId, SIGKILL))
                                {
                                    CStdError error;
                                    // print out error
                                }
                            }
                            else
                            {
                            }
                        }
                    }
                }
                catch(const std::system_error& se_exception)
                {
                }
            }, mTimeout, mProcessToWatch
        };
    }
}

void WatchDog::cancel()
{
    if(mTimeout != std::chrono::seconds(0))
    {
        std::lock_guard<std::mutex> lock(mMx);
        mCancelWatch = true;
        mCv.notify_one();
    }
}

void WatchDog::cancelAndWait()
{
    cancel();
    wait();
}

void WatchDog::convertProcessNameToPid()
{
    mProcesses = ProcessInfo::getProcessInfo(mProcessToWatch, getpid());
}

void WatchDog::wait()
{
    if(mTimeoutThread.joinable())
    {
        mTimeoutThread.join();
    }
}

WatchDog::~WatchDog()
{
    cancelAndWait();
}

}
