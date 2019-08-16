#include "Descriptor.h"

#include "Error.h"

#include <unistd.h>

using namespace std;

namespace ecu {
namespace util
{

Descriptor::Descriptor(const string& path, const DescriptorFlags flags, const FileCreationModes modes)
:   mPath{path},
    mFileDescriptor{INVALID},
    mIsOpen{false}
{
    open(mPath, flags, modes);
}

Descriptor::Descriptor(int fileDescriptor, const std::string& path)
:   mPath{path},
    mFileDescriptor{fileDescriptor}
{
    mIsOpen = false;
    if(mFileDescriptor != INVALID)
    {
        mIsOpen = true;
    }
}

Descriptor::~Descriptor()
{
    close();
}

Status Descriptor::close()
{
    Status status;
    mPath = "";
    isOpen = false;
    if(::close(mFileDescriptor) == Status::SYSTEM_ERROR)
    {
        status.createError();
    }
    mFileDescriptor = INVALID;
    return status;
}

Status Descriptor::open(const string& newPath, const DescriptorFlags flags, const FileCreationModes modes)
{
    mPath = newPath;
    mIsOpen = true;
    Status status;
    if(modes == FileCreationModes::NONE)
    {
        mFileDescriptor = ::open(path.c_str(), static_cast<int>(flags));
    }
    else
    {
        mFileDescriptor = ::open(path.c_str(), static_cast<int>(flags), static_cast<mode_t>(modes));
    }

    if(mFileDescriptor == Status::SYSTEM_ERROR)
    {
        mFileDescriptor = INVALID;
        status.createError();
        mIsOpen = false;
    }
    return status;
}

Status Descriptor::duplicate(const Descriptor newDescriptor)
{
    Status status;
    if(::dup2(mFileDescriptor, newDescriptor) == Status::SYSTEM_ERROR)
    {
        status.createError();
        return status;
    }
    return status;
}

int Descriptor::getDescriptor() const
{
    return mFileDescriptor;
}

string Descriptor::getPath() const
{
    return mPath;
}

bool Descriptor::isValid() const
{
    return (INVALID == mFileDescriptor);
}

} // util
} // ecu
