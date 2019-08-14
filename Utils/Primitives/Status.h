#ifndef UTILS_PRIMITIVES_STATUS_H
#define UTILS_PRIMITIVES_STATUS_H

#include "Error.h"

#include <string>
#include <optional>

namespace ecu
{

template <typename ResultType>
class Status
{
public:

    Status() 
    : error{nullopt},
      result{nullopt},
      message{"Operation completed successfully."}
    {}

    Status(const ResultType& r) 
    : error{nullopt},
      result{r},
      message{"Operation completed successfully."}
    {}

    Status::Status(const Error& error)
    : opt{error},
      result{nullopt},
      message{error.getError()}
    {}

    Status(const ResultType& result, const Error& error) 
    : error{error},
      result{result},
      message{error.getError()}
    {}

    Status(Status&& other)
    : error{other.error},
      result{other.result},
      message{other.message}
    {
        other.error.emplace(nullopt);
        other.result.emplace(nullopt);
        other.message = "Operation completed successfully.";
    }

    Status(const Status& other)
    : error{other.error},
      result{other.result},
      message{other.message}
    {}

    Status(const std::optional<ResultType>& other)
    : error{nullopt},
      result{other},
      message{"Operation completed successfully."}
    {}

    Status(const std::optional<Error>& other)
    : error{other},
      result{nullopt},
      message{other.has_value()?other.value.getError():""}
    {}
   
    Status(const std::optional<ResultType>& otherResult, const std::optional<Error>& otherError)
    : error{otherError},
      result{otherResult},
      message{other.has_value()?other.value.getError():""}
    {}

    virtual ~Status();

    Status& operator=(const Status& rhs)
    {
        if(&rhs == this)
            return *this;

        error = rhs.error;
        result = rhs.result;
        message = rhs.message;
        return *this;
    }

    Status& operator=(Status&& rhs)
    {
        if(&rhs == this)
            return *this;

        error = rhs.error;
        rhs.error = nullopt;
        result = rhs.result;
        rhs.result = nullopt;
        message = rhs.message;
        rhs.message = "";
        return *this;
    }

    void createError()
    {
        Error error;
        error.emplace(error);
        result.emplace(nullopt);
        message = error.getError();
    }

    void createError(const Error& error)
    {
        error.emplace(error);
        result.emplace(nullopt);
        message = error.getError();
    }

    void createSuccess()
    {
        error.emplace(nullopt);
        result.emplace(nullopt);
        message = "Operation completed successfully.";
    }

    void createSuccess(const ResultType& result)
    {
        error.emplace(nullopt);
        result.emplace(result);
        message = "Operation completed successfully.";
    }

    std::string getMessage() const
    {
        return message;
    }

    bool hasResult() const
    {
        return result.has_value();
    }

    bool hasError() const
    {
        return error.has_value();
    }
    
private:
    std::optional<Error> error;
    std::optional<ResultType> result;
    std::string message;
};

}   // ecu

#endif  // UTILS_PRIMITIVES_STATUS_H
