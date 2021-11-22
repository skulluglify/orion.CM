#include<iostream>
#include"include/orion/core.h"

typedef Ex::List<u8> List;

int main(const int argc, const char** argv) noexcept {

    (void)argc;
    (void)argv;

    List *array;
    array = new List();

    (void)(*array);

    return 0;
}
