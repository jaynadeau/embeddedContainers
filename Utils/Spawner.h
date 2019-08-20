#ifndef SPAWNER_H
#define SPAWNER_H

#include "Pipe.h"
#include "Process.h"
#include "Status.h"

#include <chrono>
#include <string>

namespace ec {
namespace util {

using namespace std::chrono_literals;

class Spawner
{
public:

    Spawner() = delete;
    Spawner(const std::string& cmd, const std::string& arguments = "", std::chrono::seconds timeout = 0s);
    Spawner(const Spawner&) = delete;
    Spawner(Spawner&&) = delete;
    virtual ~Spawner() = default;

    Spawner& operator=(const Spawner&) = delete;
    Spawner& operator=(Spawner&&) = delete;

    Status<bool> spawn(const std::string& cmd = "", const std::string& arguments = "", std::chrono::seconds timeout = 0s);
    Status<bool> spawnAndWait();
    Status<bool> wait();
    Status<bool> kill();
private:
    std::string mCommand;
    std::string mArguments;
    std::chrono::seconds mTimeout;
    Process mProcess;
    Pipe mPipe;
};

} // util
} // ec

#endif // SPAWNER_H
