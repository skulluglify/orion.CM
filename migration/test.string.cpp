#include<iostream>
#include<bitset>
#include"include/orion/core.h"

void displayByBin(Ex::List<u8>& buffer) {

    u8 n;
    bool e;
    e = true; 

    for (u64 i = 0; i < buffer.size(); i++) {

        n = buffer[i];

        std::cout << std::bitset<8>(n);
        if (i > 0 && !((i + 1) % 4)) {
            std::cout << std::endl;
            e = false;
        } else {
            std::cout << " ";
            e = true;
        }
    }

    if (!!e) std::cout << std::endl;

}

void displayByBin(Ex::List<u16>& buffer) {

    u16 n;
    bool e;
    e = true; 

    for (u64 i = 0; i < buffer.size(); i++) {

        n = buffer[i];

        std::cout << std::bitset<8>((n >> 8) & 0xFF) << " ";
        std::cout << std::bitset<8>(n & 0xFF);
        if (i > 0 && !((i + 1) % 2)) {
            std::cout << std::endl;
            e = false;
        } else {
            std::cout << " ";
            e = true;
        }
    }

    if (!!e) std::cout << std::endl;

}

void displayByBin(Ex::List<u32>& buffer) {

    u32 n;

    for (u64 i = 0; i < buffer.size(); i++) {

        n = buffer[i];

        LOG(std::bitset<8>((n >> 24) & 0xFF) << " " << std::bitset<8>((n >> 16) & 0xFF) << " " << std::bitset<8>((n >> 8) & 0xFF) << " " << std::bitset<8>(n & 0xFF))
    }

}

void push(String& str, u32 v) {
    str.push(v);
}

void push(vchar& vc, u32 v) {
    vc.push(v);
}

int main(const int argc, const char** argv) noexcept {

    (void)argc;
    (void)argv;

    String str;
    String cpy;

    push(str, (int)'H');
    push(str, (int)'e');
    push(str, (int)'l');
    push(str, (int)'l');
    push(str, (int)'o');
    push(str, (int)' ');
    push(str, (int)'W');
    push(str, (int)'o');
    push(str, (int)'r');
    push(str, (int)'l');
    push(str, (int)'d');
    push(str, (int)'!');
    push(str, (int)' ');
    push(str, 128513); // octal

    auto& utf8 = str.utf8encode();
    auto& utf16 = str.utf16encode();
    auto& utf32 = str.utf32encode();

    displayByBin(utf8);

    std::cout << std::endl;

    displayByBin(utf16);

    std::cout << std::endl;

    displayByBin(utf32);

    std::cout << std::endl;

    cpy.utf32decode(utf32);

    auto& cutf8 = cpy.utf8encode();

    displayByBin(cutf8);

    vchar vc;

    push(vc, (int)'H');
    push(vc, (int)'e');
    push(vc, (int)'l');
    push(vc, (int)'l');
    push(vc, (int)'o');
    push(vc, (int)' ');
    push(vc, (int)'W');
    push(vc, (int)'o');
    push(vc, (int)'r');
    push(vc, (int)'l');
    push(vc, (int)'d');
    push(vc, (int)'!');
    push(vc, (int)' ');
    push(vc, 128513); // octal
    push(vc, 0); // octal
    push(vc, 0); // octal
    push(vc, 0); // octal

    std::cout << std::endl;

    displayByBin(vc.getBuffer());

    std::cout << std::endl;

    LOG("size: " << vc.size())

    std::cout << std::endl;
    
    displayByBin(vc.utf32encode());
    
    std::cout << std::endl;
    
    String test(vc.utf32encode());

    displayByBin(test.utf16encode());

    return 0;
}
