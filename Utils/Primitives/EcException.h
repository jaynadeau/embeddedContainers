#ifndef EC_EXCEPTION_H
#define EC_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace ec {
namespace util {

class EcException : public std::exception
{
public:
    EcException() = delete;
    explicit EcException(const std::string& what);
    EcException(const EcException&) = default;
    EcException(EcException&&) = default;
    virtual ~EcException() = default;

    EcException& operator=(const EcException&) = default;
    EcException& operator=(EcException&&) = default;

    virtual std::string what();
private:
    std::string mMessage;
};

} // util
} // ec


#endif // EC_EXCEPTION_H
