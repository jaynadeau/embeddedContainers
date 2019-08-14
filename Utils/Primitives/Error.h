#ifndef UTILS_PRIMITIVES_ERROR_H
#define UTILS_PRIMITIVES_ERROR_H

#include <string>

namespace ecu
{

class Error
{
public:
    Error();
    Error(const Error& other) = default;
    ~Error() = default;

    Error& operator=(const Error& rhs) = default;

    std::string getErrorDescription() const;
    int getErrorNumber() const;
    std::string getError() const;

private:
    std::string errorDescription;
    int errorNumber;

    static constexpr int TMP_BUF_SIZE = 256;
};

}   // ecu

#endif  // UTILS_PRIMITIVES_ERROR_H
