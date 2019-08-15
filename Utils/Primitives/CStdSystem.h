#ifndef C_STD_SYSTEM_H
#define C_STD_SYSTEM_H

#include "CStdError.h"
#include "CStdSystemResult.h"

#include <string>

namespace ecu {
namespace util {

class CStdSystem
{
public:
    CStdSystem() = delete;
    CStdSystem(const std::string& cmd, const std::string& arguments = "");
    CStdSystem(const CStdSystem& other) = default;
    virtual ~CStdSystem() = default;

    CStdSystem operator=(const CStdSystem& rhs) = default;

    CStdSystemResult getResult() const;
    bool isSuccessful() const;
private:
    std::string mArguments;
    std::string mCmd;
    std::string mDescription;
    int mExitStatus;
    bool mSystemSucceeded;
};

} // util
} // ecu

#endif // C_STD_SYSTEM_H
