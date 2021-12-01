#include<iostream>
#include<bitset>

using namespace std;

#define LOG(x) cout << x << endl;

typedef unsigned int u32;

u32 fromCodePoint (u32 n) {

if      (n < 0x100)   return n;
else if (n < 0x800)   return 0xc000 + ((n & 0x7c0) << 2) + 0x80 + (n & 0x3f);
else if (n < 0x10000) return 0xe00000 + ((n & 0xf000) << 4) + 0x8000 + ((n & 0xfc0) << 2) + 0x80 + (n & 0x3f);
else                  return 0xf0000000 + ((n & 0x3c0000) << 6) + 0x800000 + ((n & 0x3f000) << 4) + 0x8000 + ((n & 0xfc0) << 2) + 0x80 + (n & 0x3f);

}

u32 codePointAt  (u32 n) {

if      (n < 0x100)     return n;
else if (n < 0x10000)   return ((n & 0x1f00) >> 2) + (n & 0x3f);
else if (n < 0x1000000) return ((n & 0xf0000) >> 4) + ((n & 0x3f00) >> 2) + (n & 0x3f);
else                    return ((n & 0xf000000) >> 6) + ((n & 0x3f0000) >> 4) + ((n & 0x3f00) >> 2) + (n & 0x3f);

}

int main(const int argc, const char** argv) noexcept {

    (void)argc;
    (void)argv;

    u32 n;

    cin >> n;

    LOG(bitset<32>(fromCodePoint(n)))

    LOG(((codePointAt(fromCodePoint(n)) == n) ? "yes" : "no"))

    return 0;
}
