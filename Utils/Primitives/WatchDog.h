#ifndef WATCH_DOG_H
#define WATCH_DOG_H

#include <util/ProcessInfo.h>

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace ec {
namespace util {

class WatchDog
{
public:
    WatchDog(const std::string& processToWatch, std::chrono::seconds timeout);
    WatchDog() = delete;
    ~WatchDog();

    WatchDog(const WatchDog&) = delete;    
    WatchDog(WatchDog&&) = delete;  
    WatchDog& operator=(const WatchDog&) = delete;
    WatchDog& operator=(WatchDog&&) = delete;

    void cancel();
    void cancelAndWait();
    void wait();
private:
    void convertProcessNameToPid();

    bool mCancelWatch = false;
    std::string mProcessToWatch;
    std::vector<ProcessInfo> mProcesses;
    std::chrono::seconds mTimeout;
    std::condition_variable mCv;
    std::mutex mMx;
    std::thread mTimeoutThread;
};

} // util
} // ec

#endif // WATCH_DOG_H
