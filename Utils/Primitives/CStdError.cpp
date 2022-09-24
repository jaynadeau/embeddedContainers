#include <util/CStdError.h>

#include <sstream>

#include <errno.h>
// Use the POSIX version of strerror_r instead of the GNU-specific version...
#define __USE_XOPEN2K 1
#ifdef __USE_GNU
#undef __USE_GNU
#include <string.h>
#define __USE_GNU 1
#else
#include <string.h>
#endif

namespace ec {
namespace util {

CStdError::CStdError()
: mErrorNumber{errno}
{
    char tmpBuf[TMP_BUF_SIZE];
    int result = strerror_r(mErrorNumber, tmpBuf, TMP_BUF_SIZE);
    switch(result)
    {
    case 0:
        mErrorMessage.assign(tmpBuf);
        break;
    case EINVAL:
        mErrorMessage.assign("strerror_r: The value of errno is not a valid error number.");
        break;
    case ERANGE:
        mErrorMessage.assign("strerror_r: Insufficient storage was supplied to contain the error description string.");
        break;
    default:
        mErrorMessage.assign("");
        break;
    }
}

std::string CStdError::getErrorAsString() const
{
    std::stringstream ss;
    ss << "Error number: " << mErrorNumber << " Error message: " << mErrorMessage;
    return ss.str();
}

std::string CStdError::getErrorMessage() const
{
    return mErrorMessage;
}

int CStdError::getErrorNumber() const
{
    return mErrorNumber;
}

} // util
} // ec
