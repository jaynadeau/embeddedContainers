#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H

#include <memory>
#include <string>
#include <vector>

#include <dirent.h>

namespace ec {
namespace util {

class ProcessInfo
{
public:
    ProcessInfo();
    ProcessInfo(int pid, int ppid);
    static std::vector<ProcessInfo> getProcessInfo(const std::string& processName, int parentProcessId = -1);
    ~ProcessInfo() = default;

    ProcessInfo(const ProcessInfo&) = default;    
    ProcessInfo(ProcessInfo&&) = default;  
    ProcessInfo& operator=(const ProcessInfo&) = default;
    ProcessInfo& operator=(ProcessInfo&&) = default;    

    int getParentPid() const;
    int getPid() const;
private:
    using DirContentFilter = int(*)(const struct dirent*);
    using DirEntPtr = std::unique_ptr<struct dirent>;

    static std::vector<DirEntPtr> getDirContents(const std::string& path, DirContentFilter filter);
    static ProcessInfo parseProcessInfo(const std::string& processDir);
    static ProcessInfo parseLinuxProcessInfo(const std::string& processDir);

    int mPid;
    int mPpid;
    static const std::string PROC_PATH;
};

} // util
} // ec

#endif // PROCESS_INFO_H  
