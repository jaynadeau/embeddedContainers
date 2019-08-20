#ifndef ERROR_H
#define ERROR_H

#include <string>

namespace ec {
namespace util {

class Error
{
public:
    Error();
    Error(const Error& other) = default;
    Error(Error&& other) = default;
    ~Error() = default;

    Error& operator=(const Error& rhs) = default;
    Error& operator=(Error&& rhs) = default;

    std::string getErrorDescription() const;
    int getErrorNumber() const;
    std::string getError() const;

private:
    std::string mErrorDescription;
    int mErrorNumber;

    static constexpr int TMP_BUF_SIZE = 256;
};

} // util
} // ec

#endif  // ERROR_H
