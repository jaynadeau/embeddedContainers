//
// CONFIDENTIAL - FORD MOTOR COMPANY
//
// This is an unpublished work, which is a trade secret, created in
// 2019.  Ford Motor Company owns all rights to this work and intends
// to maintain it in confidence to preserve its trade secret status.
// Ford Motor Company reserves the right to protect this work as an
// unpublished copyrighted work in the event of an inadvertent or
// deliberate unauthorized publication.  Ford Motor Company also
// reserves its rights under the copyright laws to protect this work
// as a published work.  Those having access to this work may not copy
// it, use it, or disclose the information contained in it without
// the written authorization of Ford Motor Company.
//
#include <util/WatchDog.h>

#include <util/CStdError.h>
#include <util/file_util.h>
#include <util/string_util.h>
#include <quip_logging.h>

#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <stdexcept>

#include <signal.h>
#include <sys/types.h>
#if defined(__QNXNTO__)
#include <process.h>
#else
#include <unistd.h>
#endif

namespace fnv {
namespace reconn {
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
                        QUIP_PRINT(nullptr, LV4, "Process %s timed out after %d seconds and will be killed.", mProcessToWatch.c_str(), timeout);
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
                                    QUIP_PRINT(nullptr, LV0, "Could not kill process %s, kill() returned an error: %s.", mProcessToWatch.c_str(), error.getErrorAsString().c_str());
                                }
                                QUIP_PRINT(nullptr, LV4, "Killed pid: %d, from process: %s with parent: %d.", processId, mProcessToWatch.c_str(), process.getParentPid());
                            }
                            else
                            {
                                QUIP_PRINT(nullptr, LV2, "Invalid pid: %d, from process: %s.", processId, mProcessToWatch.c_str());
                            }
                        }
                    }
                }
                catch(const std::system_error& se_exception)
                {
                    QUIP_PRINT(nullptr, LV0, "System error exception thrown: %s.", se_exception.what());
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
    QUIP_PRINT(nullptr, LV0, "Waiting for WatchDog timeout thread in WatchDog destructor.");
    cancelAndWait();
}

} // util
} // reconn
} // fnv
