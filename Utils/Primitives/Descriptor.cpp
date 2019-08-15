#include "Descriptor.h"

#include "Error.h"

#include <unistd.h>

using namespace std;

namespace ecu {
namespace util
{

Descriptor::Descriptor(const string& path, const DescriptorModes mode)
:   mPath{path},
    mFileDescriptor{INVALID},
    mIsOpen{false}
{
    open(mPath, mode);
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
    return status;
}

Status Descriptor::open(const string& newPath, const DescriptorModes mode)
{
    mPath = newPath;
    mIsOpen = true;
    Status status;
    if((mFileDescriptor = ::open(path.c_str(), static_cast<int>(mode))) == Status::SYSTEM_ERROR)
    {
        status.createError();
        mIsOpen = false;
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

} // util
} // ecu
