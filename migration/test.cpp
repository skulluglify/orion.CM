#include<iostream>
#include"include/orion/core.h"

typedef Se::List<u8> List;

int main(const int argc, const char** argv) noexcept {

    (void)argc;
    (void)argv;

    List *array;
    array = new List();


    array->push(1);
    array->push(2);
    array->push(3); //
    array->push(4); //
    array->push(5); //
    array->push(6); //
    array->push(7);
    array->push(8);
    array->push(9);
    array->push(0);

    array->splice(2, 4, 1, 2, 3, 4);
    array->display<int>();
    array->splice(0, 0, 64);

    array->display<int>();
    array->remove(2);

    array->display<int>();

    array->destroy();

    return 0;
}
