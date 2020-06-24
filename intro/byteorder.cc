#include <iostream>

#include "unp.h"

using namespace std;

int main(int argc, char const *argv[])
{
    union {
        short s;
        char c[sizeof(short)];
    } un ;
    un.s = 0x0102;
    cout << CPU_VENDOR_OS<<":";
    if(sizeof(short) == 2)
    {
        if(un.c[0] == 0x01 && un.c[1] == 0x02)
        {
            cout << "big-endial" << endl;
        }
        else if(un.c[0] == 0x02 && un.c[1] == 0x01)
        {
            cout << "little-endial" << endl;
        }
        else
        {
            cout << "unknown" << endl;
        }
    }
    else
    {
        cout << "sizeof(short)="<< sizeof(short)<< endl;
    }
    return 0;
}

