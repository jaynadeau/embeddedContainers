#include "CStdSystemResult.h"

namespace ecu {
namespace util {

CStdSystemResult::CStdSystemResult(int returnValue, std::string returnDescription)
    : mResult(std::make_pair(returnValue, returnDescription))
{
}

std::string CStdSystemResult::getResultAsString() const
{
    return std::string{"Return code: " + std::to_string(mResult.first) + ", Description: " + mResult.second};
}

int CStdSystemResult::getResultCode() const
{
    return mResult.first;
}

} // util
} // ecu
