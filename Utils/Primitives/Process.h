#ifndef PROCESS_H
#define PROCESS_H

#include <unistd.h>

namespace ec {
namespace util {

class Process
{
public:
    Process();
    virtual ~Process() = default;

    Process(const Process&) = delete;
    Process(Process&&) = delete;
    Process& operator=(const Process&) = delete;
    Process& operator=(Process&&) = delete;

    bool isChild() const;
private:
    pid_t mChildProcessId;
};

} // util
} // ec

#endif // PROCESS_H
