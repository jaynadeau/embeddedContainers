#include "CStdError.h"

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

namespace ecu {
namespace util {

CStdError::CStdError()
: mErrorNumber{errno}
{
    char tmpBuf[TMP_BUF_SIZE];
    int result = strerror_r(mErrorNumber, tmpBuf, TMP_BUF_SIZE);
    switch(result)
    {
    case 0:
        mErrorDescription.assign(tmpBuf);
        break;
    case EINVAL:
        mErrorDescription.assign("strerror_r: The value of errno is not a valid error number.");
        break;
    case ERANGE:
        mErrorDescription.assign("strerror_r: Insufficient storage was supplied to contain the error description string.");
        break;
    default:
        mErrorDescription.assign("");
        break;
    }
}

string CStdError::getErrorDescription() const
{
    return mErrorDescription;
}

int CStdError::getErrorNumber() const
{
    return mErrorNumber;
}

string CStdError::getError() const
{
    stringstream ss;
    ss << "Error number: " << mErrorNumber << ", Description: " << mErrorDescription;
    return ss.str();
}

} // util
} // ecu
