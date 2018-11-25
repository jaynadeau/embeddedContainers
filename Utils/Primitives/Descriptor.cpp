#include "Descriptor.h"

#include "Error.h"

#include <unistd.h>

using namespace std;

namespace ecu
{

Descriptor::Descriptor(const string& path, const DescriptorModes mode)
:   path{path},
    fileDescriptor{INVALID},
    isOpen{false}
{
    open(path, mode);
}

Descriptor::~Descriptor()
{
    close();
}

Status Descriptor::close()
{
    Status status;
    path = "";
    isOpen = false;
    if(::close(fileDescriptor) == Status::SYSTEM_ERROR)
    {
        status.createError();
    }
    return status;
}

Status Descriptor::open(const string& newPath, const DescriptorModes mode)
{
    path = newPath;
    isOpen = true;
    Status status;
    if((fileDescriptor = ::open(path.c_str(), static_cast<int>(mode))) == Status::SYSTEM_ERROR)
    {
        isOpen = false;
        status.createError();
    }
    return status;
}

int Descriptor::getDescriptor() const
{
    return fileDescriptor;
}

string Descriptor::getPath() const
{
    return path;
}

};
