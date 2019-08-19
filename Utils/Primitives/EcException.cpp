#include "EcException.h"

namespace ec {
namespace util {

EcException::EcException(const std::string& what)
: mMessage{what}
{

}

std::string EcException::what()
{
    return mMessage;
}

} // util
} // ec