#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include "Status.h"

#include <string>

#include <fcntl.h>
#include <sys/stat.h>

namespace ecu {
namespace util {

class Descriptor
{
public:

    enum class FileCreationModes : mode_t
    {
        USER_ALL            = S_IRWXU,
        USER_READ           = S_IRUSR,
        USER_WRITE          = S_IWUSR,
        USER_EXECUTE        = S_IXUSR,
        GROUP_ALL           = S_IRWXG,
        GROUP_READ          = S_IRGRP,
        GROUP_WRITE         = S_IWGRP,
        GROUP_EXECUTE       = S_IXGRP,
        OTHERS_ALL          = S_IRWXO,
        OTHERS_READ         = S_IROTH,
        OTHERS_WRITE        = S_IWOTH,
        OTHERS_EXECUTE      = S_IXOTH, 
        SET_USER_ID_BIT     = S_ISUID,
        SET_GROUP_ID_BIT    = S_ISGID,
        SET_STICKY_BIT      = S_ISVTX,
        NONE                = -1,
    };
    
    enum class DescriptorFlags : unsigned int
    {
        READ_WRITE          = O_RDWR,
        CREATE_FILE         = O_CREAT,
        APPEND_TO_FILE      = O_APPEND,
        READ_ONLY           = O_RDONLY,
        WRITE_ONLY          = O_WRONLY,
        EXCLUSIVE           = O_EXCL,
        NO_CONTROLLING_TTY  = O_NOCTTY,
        NON_BLOCKING        = O_NONBLOCK,
        FLUSH_DATA_METADATA = O_SYNC,
        FLUSH_DATA          = O_DSYNC,
        FLUSH_ON_READ       = O_RSYNC,
        TRUNCATE            = O_TRUNC,
        RDWR_CREATE_APPEND  = O_RDWR | O_CREAT | O_APPEND,
        /*ASYNCHRONOUS        = O_ASYNC,*/ // known kernel bug, does not work
        CLOSE_ON_EXEC       = O_CLOEXEC,
        DIRECT_IO           = O_DIRECT,
        IS_DIRECTORY_ONLY   = O_DIRECTORY,
        NOFOLLOW_SYM_LINKS  = O_NOFOLLOW,
        INIT_TTY_PARAMS     = O_TTY_INIT,
    };

    static constexpr int INVALID = -1;

    Descriptor(const std::string& path, const DescriptorFlags flags = DescriptorFlags::RDWR_CREATE_APPEND, const FileCreationModes modes = FileCreationModes::NONE);
    Descriptor() = delete;
    Descriptor(int fileDescriptor, const std::string& path = std::string{""});
    ~Descriptor();

    // assignment

    Status close();
    Status open(const std::string& newPath, const DescriptorFlags flags = DescriptorFlags::RDWR_CREATE_APPEND, const FileCreationModes modes = FileCreationModes::NONE);
    Status duplicate();

    int getDescriptor() const;
    std::string getPath() const;
    bool isValid() const;
private:
    std::string mPath;
    int mFileDescriptor;
    bool mIsOpen;
};

} // util
} // ecu

#endif  // DESCRIPTOR_H
