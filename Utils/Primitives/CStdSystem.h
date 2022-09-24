#ifndef C_STD_SYSTEM_H
#define C_STD_SYSTEM_H

#include "CStdError.h"
#include "CStdSystemResult.h"

#include <chrono>
#include <string>

namespace ec {
namespace util {

class CStdSystem final
{
public:
    CStdSystem() = delete;
    CStdSystem(const std::string& cmd, const std::string& arguments = "", std::chrono::seconds timeout = std::chrono::seconds(0));
    CStdSystem(const CStdSystem& other) = default;
    ~CStdSystem() = default;

    CStdSystem& operator=(const CStdSystem& rhs) = default;

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
} // ec

#endif	// C_STD_SYSTEM_H
