#ifndef C_STD_ERROR_H
#define C_STD_ERROR_H

#include <string>

namespace ec {
namespace util {

class CStdError final
{
public:
    CStdError();
    CStdError(const CStdError& other) = default;
    ~CStdError() = default;

    CStdError& operator=(const CStdError& rhs) = default;

    std::string getErrorAsString() const;
    std::string getErrorMessage() const;
    int getErrorNumber() const;
private:
    int mErrorNumber;
    std::string mErrorMessage;

    static const int TMP_BUF_SIZE = 256;
};

} // util
} // ec

#endif	// C_STD_ERROR_H 
