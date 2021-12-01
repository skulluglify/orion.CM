#include<iostream>
#include<bitset>

using namespace std;

#define LOG(x) cout << x << endl;

typedef unsigned int u32; // 32 bits

u32 codePointAt(u32 n) { // uchar16 to oct

    if (n < 0x10000) return n;
    else {

        n = ((n & 0x3FF0000) >> 6) + (n & 0x3FF);

        return n + 0x10000;
    };

}

u32 fromCodePoint(u32 n) { // oct to uchar16

    if (n < 0x10000) return n;
    else {

        n = n - 0x10000;

        return 0xD8000000 + ((n & 0xFFC00) << 6) +
        0xDC00 + (n & 0x3FF);
    };

}

int main(const int argc, const char** argv) noexcept {

    (void)argc;
    (void)argv;

    u32 n;

    cin >> n;

    u32 v = fromCodePoint(n);

    LOG( bitset<8>((v & 0xFF000000) >> 24) << " " << bitset<8>((v & 0xFF0000) >> 16) << " " << bitset<8>((v & 0xFF00) >> 8) << " " << bitset<8>((v & 0xFF)) )

    LOG (( codePointAt(fromCodePoint(n)) == n ? "yes" : "no" ))

    LOG(codePointAt(fromCodePoint(n)))

    return 0;
}
