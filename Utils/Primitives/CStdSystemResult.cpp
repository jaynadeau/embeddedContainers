#include "CStdSystemResult.h"

namespace ec {
namespace util {

CStdSystemResult::CStdSystemResult(int returnValue, std::string returnDescription)
    : mResult(std::make_pair(returnValue, returnDescription))
{
}

std::string CStdSystemResult::getResultAsString() const
{
    return std::string{"Return code: " + std::to_string(mResult.first) + ", Description: " + mResult.second};
}

} // util
} // ec
