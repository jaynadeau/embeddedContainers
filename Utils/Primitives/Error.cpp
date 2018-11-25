#include "Error.h"

#include <sstream>

#include <errno.h>
#include <string.h>

using namespace std;

namespace ecu
{

Error::Error()
: errorNumber(0)
{
    errorNumber = errno;
    errorDescription.assign(strerror(errorNumber));
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
