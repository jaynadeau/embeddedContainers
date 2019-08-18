#ifndef STATUS_H
#define STATUS_H

#include "CStdError.h"

#include <string>
#include <optional>

namespace ecu {
namespace util {

template <typename ResultType = void>
class Status
{
public:

    Status()
    : mError{nullopt},
      mResult{nullopt},
      mMessage{"Operation completed successfully."}
    {}

    Status(const ResultType& r) 
    : mError{nullopt},
      mResult{r},
      mMessage{"Operation completed successfully."}
    {}

    Status::Status(const CStdError& error)
    : error{error},
      mResult{nullopt},
      mMessage{mError.value().getError()}
    {}

    Status(const ResultType& result, const CStdError& error) 
    : mError{error},
      mResult{result},
      mMessage{mError.value().getError()}
    {}

    Status(Status&& other)
    : mError{other.mError},
      mResult{other.mResult},
      mMessage{other.mMessage}
    {
        other.mError.emplace(nullopt);
        other.mResult.emplace(nullopt);
        other.mMessage = "";
    }

    Status(const Status& other)
    : mError{other.mError},
      mResult{other.mResult},
      mMessage{other.mMessage}
    {}

    Status(const std::optional<ResultType>& other)
    : mError{nullopt},
      mResult{other},
      mMessage{"Operation completed successfully."}
    {}

    Status(const std::optional<CStdError>& other)
    : mError{other},
      mResult{nullopt},
      mMessage{other.has_value()?other.value().getError():""}
    {}
   
    Status(const std::optional<ResultType>& otherResult, const std::optional<CStdError>& otherError)
    : mError{otherError},
      mResult{otherResult},
      mMessage{otherError.has_value()?otherError.value().getError():""}
    {}

    virtual ~Status() = default;

    Status& operator=(const Status& rhs)
    {
        if(&rhs == this)
            return *this;

        mError = rhs.mError;
        mResult = rhs.mResult;
        mMessage = rhs.mMessage;
        return *this;
    }

    Status& operator=(Status&& rhs)
    {
        if(&rhs == this)
            return *this;

        mError = rhs.mError;
        rhs.mError = nullopt;
        mResult = rhs.mResult;
        rhs.mResult = nullopt;
        mMessage = rhs.mMessage;
        rhs.mMessage = "";
        return *this;
    }

    Status& operator=(const ResultType& r)
    {
        mError.emplace(nullopt);
        mResult.emplace(r);
        mMessage = "Operation completed successfully.";
    }

    void createError()
    {
        CStdError error;
        mError.emplace(error);
        mResult.emplace(nullopt);
        mMessage = mError.value().getError();
    }

    void createError(const CStdError& error)
    {
        mError.emplace(error);
        mResult.emplace(nullopt);
        mMessage = mError.value().getError();
    }

    void createError(const ResultType& r)
    {
        CStdError error;
        mError.emplace(error);
        mResult.emplace(r);
        mMessage = mError.value().getError();
    }

    void createSuccess()
    {
        mError.emplace(nullopt);
        mResult.emplace(nullopt);
        mMessage = "Operation completed successfully.";
    }

    void createSuccess(const ResultType& result)
    {
        mError.emplace(nullopt);
        mResult.emplace(result);
        mMessage = "Operation completed successfully.";
    }

    std::string getMessage() const
    {
        return mMessage;
    }

    bool hasResult() const
    {
        return mResult.has_value();
    }

    ResultType getResult() const
    {
        if(hasResult())
        {
            return mResult.value();
        }
        return ResultType{};
    }

    void setResult(const ResultType& r)
    {
        mResult.emplace(r);
    }

    bool hasError() const
    {
        return mError.has_value();
    }

    static constexpr int SYSTEM_ERROR = -1;
    
private:
    std::optional<CStdError> mError;
    std::optional<ResultType> mResult;
    std::string mMessage;
};

} // util
} // ecu

#endif  // STATUS_H
