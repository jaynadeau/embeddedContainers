#ifndef C_STD_SYSTEM_RESULT_H
#define C_STD_SYSTEM_RESULT_H

#include <string>
#include <utility>

namespace ecu {
namespace util {

class CStdSystemResult
{
public:
    CStdSystemResult() = delete;
    CStdSystemResult(int returnValue, std::string returnDescription);
    CStdSystemResult(const CStdSystemResult& other) = default;
    virtual ~CStdSystemResult() = default;

    CStdSystemResult& operator=(const CStdSystemResult& rhs) = default;

    std::string getResultAsString() const;
    int getResultCode() const;
private:
    std::pair<int, std::string> mResult;
};

} // util
} // ecu

#endif // C_STD_SYSTEM_RESULT_H
