#include "Spawner.h"

namespace ec {
namespace util {

Spawner::Spawner(const std::string& cmd, const std::string& arguments, std::chrono::seconds timeout)
: mCommand{cmd},
  mArguments{arguments},
  mTimeout{timeout}
{

}

Status<bool> Spawner::spawn(const std::string& cmd, const std::string& arguments, std::chrono::seconds timeout)
{
    if(!cmd.empty())
    {
        mCommand = cmd;
    }
    if(!arguments.empty())
    {
        mArguments = arguments;
    }
    if(timeout != 0s)
    {
        mTimeout = timeout;
    }
    
}

} // util
} // ec