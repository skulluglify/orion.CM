// #include <iostream>
#include "extras/orion.h"

// using namespace std;

int main(int argc, const bytearray argv) 
{
    yelp::init();
    for (int i = 0; i < argc; ++i) 
    {
        cout << argv[i] << endl;
    }
	cout << yelp::bin<uint16>(64) << endl;
    return 0;
}
