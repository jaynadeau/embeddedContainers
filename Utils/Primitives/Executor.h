#ifndef EXECUTOR_H
#define EXECUTOR_H

namespace ec {
namespace util {

class Executor
{
public:
    Executor();
    Executor(const Executor&) = default;
    Executor(Executor&&) = default;
    virtual ~Executor();

    Executor& operator=(const Executor&) = default;
    Executor& operator=(Executor&&) = default;
private:
};

} // util
} // ec

#endif // EXECUTOR_H
