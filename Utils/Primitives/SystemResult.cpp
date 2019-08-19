#include "SystemResult.h"

namespace ec {
namespace util {

SystemResult::SystemResult(int returnValue, std::string returnDescription)
    : mResult(std::make_pair(returnValue, returnDescription))
{
}

std::string SystemResult::getResultAsString() const
{
    return std::string{"Return code: " + std::to_string(mResult.first) + ", Description: " + mResult.second};
}

int SystemResult::getResultCode() const
{
    return mResult.first;
}

} // util
} // ec
