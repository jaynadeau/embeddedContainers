#include "Error.h"

#include <cerrno>
#include <sstream>

#define __USE_XOPEN2K 1
#ifdef __USE_GNU
#undef __USE_GNU
#include <string.h>
#define __USE_GNU 1
#else
#include <string.h>
#endif

using namespace std;

namespace ecu
{

Error::Error()
: errorNumber{errno}
{
    char tmpBuf[TMP_BUF_SIZE];
    int result = strerror_r(errorNumber, tmpBuf, TMP_BUF_SIZE);
    switch(result)
    {
    case 0:
        errorDescription.assign(tmpBuf);
        break;
    case EINVAL:
        errorDescription.assign("strerror_r: The value of errno is not a valid error number.");
        break;
    case ERANGE:
        errorDescription.assign("strerror_r: Insufficient storage was supplied to contain the error description string.");
        break;
    default:
        errorDescription.assign("");
        break;
    }
}

string Error::getErrorDescription() const
{
    return errorDescription;
}

int Error::getErrorNumber() const
{
    return errorNumber;
}

string Error::getError() const
{
    stringstream ss;
    ss << "Error number: " << errorNumber << ", Description: " << errorDescription;
    return ss.str();
}

}
