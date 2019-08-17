#include "Descriptor.h"

#include "CStdError.h"

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

Status<int> Descriptor::close()
{
    Status<int> status;
    mPath = "";
    mIsOpen = false;
    if(::close(mFileDescriptor) == Status<void>::SYSTEM_ERROR)
    {
        status.createError();
    }
    mFileDescriptor = INVALID;
    return status;
}

Status<int> Descriptor::open(const string& newPath, const DescriptorFlags flags, const FileCreationModes modes)
{
    mPath = newPath;
    mIsOpen = true;
    Status<int> status;
    if(modes == FileCreationModes::NONE)
    {
        mFileDescriptor = ::open(mPath.c_str(), static_cast<int>(flags));
    }
    else
    {
        mFileDescriptor = ::open(mPath.c_str(), static_cast<int>(flags), static_cast<mode_t>(modes));
    }

    if(mFileDescriptor == Status<void>::SYSTEM_ERROR)
    {
        mFileDescriptor = INVALID;
        status.createError();
        mIsOpen = false;
    }
    return status;
}

Status<int> Descriptor::duplicate(const Descriptor& newDescriptor)
{
    Status<int> status;
    if(::dup2(mFileDescriptor, newDescriptor.getDescriptor()) == Status<void>::SYSTEM_ERROR)
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
