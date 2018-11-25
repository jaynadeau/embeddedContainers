#ifndef UTILS_PRIMITIVES_STATUS_H
#define UTILS_PRIMITIVES_STATUS_H

#include "Error.h"

#include <string>
#include <optional>

namespace ecu
{

class Status
{
public:
    Status();
    Status(const Status& other);
    Status(const std::optional<Error>& other);
    Status(const Error& error);
    ~Status();

    Status& operator=(const Status& rhs);

    static const std::uint8_t SYSTEM_ERROR = -1;

    void createError();
    void createSuccess();
private:
    std::optional<Error> opt;
    bool success;
    std::string message;
};

}   // ecu

#endif  // UTILS_PRIMITIVES_STATUS_H
