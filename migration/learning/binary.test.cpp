#include<iostream>
#include<bitset>

using namespace std;

#define LOG(x) cout << x << endl;
#define BS(x) cout << bitset<8>(x) << endl;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long int u64;


int main(const int argc, const char** argv) {

    (void)argc;
    (void)argv;

    u8 ir;
    u8 r;
    u8 l;

    ir = 0;
    r = 0;
    l = 0;

    for (u8 i = 0; i <= 6; i += 2) {

        ir = 6 - i;

        r = ((1 << ir) - 1);

        l = ((1 << i) - 1) << (8 - i); // 6 - i + 2

        BS(r | l)
        
    }

    return 0;
}
