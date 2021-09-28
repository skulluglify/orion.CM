// #include <iostream>
#include "extras/orion.h"

// using namespace std;

int main(int argc, bytes argv[]) 
{
    yelp::init();
    for (int i = 0; i < argc; ++i) 
    {
        cout << argv[i] << endl;
    }
	cout << yelp::bin(255) << endl;
    return 0;
}
