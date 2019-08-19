#ifndef SYSTEM_RESULT_H
#define SYSTEM_RESULT_H

#include <string>
#include <utility>

namespace ec {
namespace util {

class SystemResult
{
public:
    SystemResult() = delete;
    SystemResult(int returnValue, std::string returnDescription);
    SystemResult(const SystemResult& other) = default;
    virtual ~SystemResult() = default;

    SystemResult& operator=(const SystemResult& rhs) = default;

    std::string getResultAsString() const;
    int getResultCode() const;
private:
    std::pair<int, std::string> mResult;
};

} // util
} // ec

#endif // SYSTEM_RESULT_H
