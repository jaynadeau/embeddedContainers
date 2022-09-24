#include <ProcessInfo.h>

#include <CStdError.h>
#include <string_util.h>

#include <algorithm>
#include <fstream>

namespace ec {
namespace util {

const std::string ProcessInfo::PROC_PATH{"/proc"};

std::vector<ProcessInfo> ProcessInfo::getProcessInfo(const std::string& processName, int parentProcessId)
{
    std::vector<ProcessInfo> processInfos;
    auto filter = [](const struct dirent* direntPtr) -> int {
        std::string dirName{direntPtr->d_name};
        if(dirName.compare(".") == 0 || dirName.compare("..") == 0)
        {
            return false;
        }
        return std::all_of(dirName.begin(), dirName.end(), ::isdigit);
    };

    std::vector<DirEntPtr> procDirContents = ProcessInfo::getDirContents(PROC_PATH, filter);
    for(const auto& dir : procDirContents)
    {
        std::string pidDir{dir->d_name};
        std::string procPath{StringUtil::slashTerminatePathStr(PROC_PATH) + pidDir};

        std::string procFileContents;
        std::string processDir{StringUtil::slashTerminatePathStr(procPath)};
        std::string procFilename{processDir + "cmdline"};
        std::ifstream processFile{procFilename};
        if(processFile.is_open())
        {
            std::getline(processFile, procFileContents);
        }
        if(std::string::npos != procFileContents.find(processName))
        {
            ProcessInfo processInfo = ProcessInfo::parseProcessInfo(processDir);
            if(processInfo.getParentPid() == parentProcessId && parentProcessId != -1)
            {
                processInfos.emplace_back(processInfo);
            }
            else
            {
                // if ppid is -1, collect all processes matching processName
                processInfos.emplace_back(processInfo);
            }
            
        }
    }
    return processInfos;
}

ProcessInfo::ProcessInfo()
: mPid{-1},
  mPpid{-1}
{
}

ProcessInfo::ProcessInfo(int pid, int ppid)
: mPid{pid},
  mPpid{ppid}
{
}

std::vector<ProcessInfo::DirEntPtr> ProcessInfo::getDirContents(const std::string& path, ProcessInfo::DirContentFilter filter)
{
    struct dirent** namelist;
    int n = scandir(path.c_str(), &namelist, filter, alphasort);
    if(n == -1)
    {
        CStdError error;
        // print out error
        return std::vector<DirEntPtr>{};
    }
    else
    {
        return std::vector<DirEntPtr>{namelist, namelist+n};
    }
}

int ProcessInfo::getPid() const
{
    return mPid;
}

int ProcessInfo::getParentPid() const
{
    return mPpid;
}

ProcessInfo ProcessInfo::parseProcessInfo(const std::string& processDir)
{
    return ProcessInfo::parseLinuxProcessInfo(processDir);
}

ProcessInfo ProcessInfo::parseLinuxProcessInfo(const std::string& processDir)
{
    auto caseInsensitiveEqual = [](const std::string& str1, const std::string& str2){
        return std::equal(str1.begin(), str1.end(), str2.begin(), [](const char& c1, const char& c2){
            return (std::toupper(c1) == std::toupper(c2));
        });
    };
    int pid;
    int ppid;
    std::ifstream processFile{StringUtil::slashTerminatePathStr(processDir) + "status"};
    std::string tmp;
    if(processFile.is_open())
    {
        processFile >> tmp;
        while(!caseInsensitiveEqual("Pid:", tmp))
        {
            processFile >> tmp;
        }
        try
        {
            processFile >> tmp;
            pid = std::stoi(tmp);
        }
        catch(const std::invalid_argument& ia_exception)
        {
            return ProcessInfo{};
        }
        catch(const std::out_of_range& oor_exception)
        {
            return ProcessInfo{};
        }
        processFile.clear();
        processFile.seekg(0, std::ios::beg);
        processFile >> tmp;
        while(!caseInsensitiveEqual("PPid:", tmp))
        {
            processFile >> tmp;
        }
        try
        {
            processFile >> tmp;
            ppid = std::stoi(tmp);
        }
        catch(const std::invalid_argument& ia_exception)
        {
            return ProcessInfo{};
        }
        catch(const std::out_of_range& oor_exception)
        {
            return ProcessInfo{};
        }
        return ProcessInfo{pid, ppid};
    }
    return ProcessInfo{};
}

} // util
} // ec
