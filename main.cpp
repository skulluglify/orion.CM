// #include <iostream>
#include "extras/orion.h"

// using namespace std;

int main(int argc, const bytearray argv) 
{
    (void)argc;
    (void)argv;
    yelp::init();
    for (int i = 0; i < argc; ++i) 
    {
        cout << argv[i] << endl;
    }
    uint16 x = 64;
    cout << yelp::bin(x) << endl;
    cout << yelp::bin<uint8>(23) << endl;
    return 0;
}
