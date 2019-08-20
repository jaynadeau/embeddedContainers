#ifndef PROCESS_H
#define PROCESS_H

#include <unistd.h>

namespace ec {
namespace util {

class Process
{
public:
    Process();
    Process(const Process&) = default;
    Process(Process&&) = default;
    virtual ~Process() = default;

    Process& operator=(const Process&) = default;
    Process& operator=(Process&&) = default;

    bool isChild() const;
private:
    pid_t mChildProcessId;
};

} // util
} // ec

#endif // PROCESS_H
