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

    enum class DescriptorModes : unsigned int
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
    };

    static const int INVALID = -1;

    Descriptor(const std::string& path, const DescriptorModes mode = DescriptorModes::RDWR_CREATE_APPEND);
    // copy
    Descriptor() = delete;
    ~Descriptor();

    // assignment

    Status open(const std::string& newPath, const DescriptorModes mode = DescriptorModes::RDWR_CREATE_APPEND);
    Status close();

    int getDescriptor() const;
    std::string getPath() const;
private:
    std::string mPath;
    int mFileDescriptor;
    bool mIsOpen;
};

} // util
} // ecu

#endif  // DESCRIPTOR_H
