
#include "Utils/Streams/fdstreambuf.h"

#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
    ecio::basic_fdstreambuf buf("myfile.txt");

    ostream out(&buf);

    out << "31 hexadecimal: " << std::hex << 31 << endl;

    return 0;
}
