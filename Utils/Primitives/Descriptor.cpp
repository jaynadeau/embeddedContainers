#include "Descriptor.h"

#include "CStdError.h"

#include <unistd.h>

using namespace std;

namespace ecu {
namespace util
{

Descriptor::Descriptor()
: mFileDescriptor(INVALID),
  mIsOpen(false)
  {
      
  }

Descriptor::Descriptor(const string& path, const DescriptorFlags flags, const FileCreationModes modes)
:   mPath{path},
    mFileDescriptor{INVALID},
    mIsOpen{false}
{
    Status<bool> status = open(mPath, flags, modes);
    if(status.hasError())
    {
        // throw exception
    }
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

Status<bool> Descriptor::close()
{
    Status<bool> status{true};
    if(::close(mFileDescriptor) == Status<void>::SYSTEM_ERROR)
    {
        status.createError(false);
    }
    else
    {
        mPath = "";
        mFileDescriptor = INVALID;
        mIsOpen = false;
    }
    
    return status;
}

Status<bool> Descriptor::open(const string& newPath, const DescriptorFlags flags, const FileCreationModes modes)
{
    mPath = newPath;
    mIsOpen = true;
    Status<bool> status{true};
    if(modes == FileCreationModes::NONE)
    {
        mFileDescriptor = ::open(mPath.c_str(), static_cast<int>(flags));
    }
    else
    {
        mFileDescriptor = ::open(mPath.c_str(), static_cast<int>(flags), static_cast<mode_t>(modes));
    }

    if(mFileDescriptor == INVALID)
    {
        status.createError(false);
        mIsOpen = false;
    }
    return status;
}

Status<bool> Descriptor::duplicate(const Descriptor& newDescriptor)
{
    Status<bool> status{true};
    if(::dup2(mFileDescriptor, newDescriptor.getDescriptor()) == Status<void>::SYSTEM_ERROR)
    {
        status.createError(false);
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
