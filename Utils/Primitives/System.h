#ifndef SYSTEM_H
#define SYSTEM_H

#include "Error.h"
#include "SystemResult.h"

#include <string>

namespace ec {
namespace util {

class System
{
public:
    System() = delete;
    System(const std::string& cmd, const std::string& arguments = "");
    System(const System& other) = default;
    virtual ~System() = default;

    System operator=(const System& rhs) = default;

    SystemResult getResult() const;
    bool isSuccessful() const;
private:
    std::string mArguments;
    std::string mCmd;
    std::string mDescription;
    int mExitStatus;
    bool mSystemSucceeded;
};

} // util
} // ec

#endif // SYSTEM_H
