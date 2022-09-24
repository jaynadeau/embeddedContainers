#ifndef C_STD_SYSTEM_RESULT_H
#define C_STD_SYSTEM_RESULT_H

#include <string>
#include <utility>

namespace ec {
namespace util {

class CStdSystemResult final
{
public:
    CStdSystemResult() = delete;
    CStdSystemResult(int returnValue, std::string returnDescription);
    CStdSystemResult(const CStdSystemResult& other) = default;
    ~CStdSystemResult() = default;

    CStdSystemResult& operator=(const CStdSystemResult& rhs) = default;

    std::string getResultAsString() const;
private:
    std::pair<int, std::string> mResult;
};

} // util
} // ec

#endif	// C_STD_SYSTEM_RESULT_H
