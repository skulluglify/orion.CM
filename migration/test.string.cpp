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

int main(const int argc, const char** argv) noexcept {

    (void)argc;
    (void)argv;

    String str;

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

    return 0;
}
