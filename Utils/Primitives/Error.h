#ifndef UTILS_PRIMITIVES_ERROR_H
#define UTILS_PRIMITIVES_ERROR_H

#include <string>

namespace ecu
{

class Error
{
public:
    Error();
    ~Error() {};

    std::string getErrorDescription() const;
    int getErrorNumber() const;
    std::string getError() const;

private:
    std::string errorDescription;
    int errorNumber;
};

}   // ecu

#endif  // UTILS_PRIMITIVES_ERROR_H
