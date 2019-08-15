#ifndef C_STD_ERROR_H
#define C_STD_ERROR_H

#include <string>

namespace ecu {
namespace util {

class CStdError
{
public:
    CStdError();
    CStdError(const CStdError& other) = default;
    ~CStdError() = default;

    CStdError& operator=(const CStdError& rhs) = default;

    std::string getErrorDescription() const;
    int getErrorNumber() const;
    std::string getError() const;

private:
    std::string mErrorDescription;
    int mErrorNumber;

    static constexpr int TMP_BUF_SIZE = 256;
};

} // util
} // ecu

#endif  // C_STD_ERROR_H
