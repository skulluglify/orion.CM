#include<iostream>
#include<bitset>

using namespace std;

#define LOG(x) cout << x << endl;

typedef unsigned int u32;

u32 codePointAt(u32 n) {

    if      (n < 0x100    ) return n;
    else if (n < 0x10000  ) return                             ((n & 0x1F00) >> 2) + (n & 0x3F);
    else if (n < 0x1000000) return     ((n & 0xF0000 ) >> 4) + ((n & 0x3F00) >> 2) + (n & 0x3F);
    // < 0x100000000
    else return ((n & 0x7000000) >> 6) + ((n & 0x3F0000) >> 4) + ((n & 0x3F00) >> 2) + (n & 0x3F);
}

u32 fromCodePoint(u32 n) {

    // 0o77       0x3f
    // 0o7700     0xfc0
    // 0o770000   0x3f000
    // 0o77000000 0xfc0000

    if      (n < 0x80   ) return n;
    else if (n < 0x800  ) return                                                       0xC000 + ((n & 0xfc0) << 2) + 0x80 + (n & 0x3f);
    else if (n < 0x10000) return                     0xE00000 + ((n & 0x3f000) << 4) + 0x8000 + ((n & 0xfc0) << 2) + 0x80 + (n & 0x3f);
    // < 0x200000
    else return 0xF0000000 + ((n & 0xfc0000) << 6) + 0x800000 + ((n & 0x3f000) << 4) + 0x8000 + ((n & 0xfc0) << 2) + 0x80 + (n & 0x3f);
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
