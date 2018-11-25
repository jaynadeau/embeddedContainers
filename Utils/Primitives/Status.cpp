#include "Status.h"

using namespace std;

namespace ecu
{

Status::Status()
: opt{nullopt},
  success(true),
  message{"Operation completed successfully."}
{}

Status::Status(const Status& other)
: opt{other.opt},
  success{other.success},
  message{other.message}
{}

Status::Status(const optional<Error>& other)
: opt{other},
  success{!other.has_value()},
  message{other.has_value()?other.value.getError():""}
{}

Status::Status(const Error& error)
:   opt{error},
    success{false},
    message{error.getError()}
{}

Status& Status::operator=(const Status& rhs)
{
    opt = rhs.opt;
    success = rhs.success;
    message = rhs.message;
    return *this;
}

void Status::createError()
{
    Error error;
    opt.emplace(error);
    success = false;
    message = error.getError();
}

void Status::createSuccess()
{
    opt.emplace(nullopt);
    success = true;
    message = "Operation completed successfully.";
}

}   // ecu
