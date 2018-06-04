
#include "Utils/Streams/fdstreambuf.h"

#include <iostream>
#include <string>

using namespace std;


int main(int argc, char const *argv[])
{
    ecio::basic_fdstreambuf outbuf("myfile.txt");

    ostream out(&outbuf);

    out << "31 hexadecimal: " << std::hex << 31 << endl;

    ecio::basic_fdstreambuf inbuf("myfile.txt");
    istream in(&inbuf);


    char c;
    string textBuffer;
    while(!in.eof())
    {
        in >> noskipws >> c;
        textBuffer += c;
    }

    cout << textBuffer;

    cout << "embeddedContainers exiting..." << endl;

    return 0;
}
