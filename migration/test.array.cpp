#include<iostream>
#include"include/orion/core.h"

typedef Ex::List<u8> List;

int main(const int argc, const char** argv) noexcept {

    (void)argc;
    (void)argv;

    List *array;
    List *copy;
    array = new List();

    (void)(*array);

    for (int i = 0; i < 20; i++) {

        LOG("================================")

        array->push((u8)i);
        LOG((int)array->getitem(i).data);
        array->setitem(i, (u8)((i + 1) * 2));
        LOG("size:" << array->size())
        array->display();
    }

    copy = &array->copy();

    for (int i = 0; i < 10; i++) {

        LOG("================================")

        array->remove(0);
        array->display();
    }

    for (int i = 0; i < 10; i++) {

        LOG("================================")

        array->remove(array->size() - 1);
        array->display();
    }

    array = &copy->copy();

    for (int i = 5; i < 12; i++) {

        LOG("================================")

        LOG(i)

        array->remove(i);
        array->display();
    }

    array = &copy->concat(*array);

    array->display();

    LOG((int)array->shift())
    LOG((int)array->pop())

    array->display();

    LOG("size: " << array->size())

    for (u64 i = 0; i < array->size(); i++) {
        u8 data = array->getitem(i).valueOf();
        LOG("data: " << (int)data)
        LOG(array->indexOf(data).valueOf())
    }

    array->display();

    array->reverse();

    for (u64 i = 0; i < array->size(); i++) {
        u8 data = array->getitem(i).valueOf();
        array->setitem(i, data  + 1);
    }

    array->display();

    for (u64 i = 0; i < array->size(); i++) {
        u8 data = array->getitem(i).valueOf();
        LOG("data: " << (int)data)
        LOG((array->includes(data) ? "true" : "false"))
    }

    array->display();

    copy = &array->copy();

    array = &array->slice(0, 4);

    array->display();

    array = &copy->copy();

    array = &array->slice(4, array->size());

    array->display();

    array = &copy->copy();
    
    array->display();

    array->splice(2, 4);

    array->display();

    array = &copy->copy();
    
    array->splice(2, 4, 1, 2, 3, 4, 12);

    array->display();

    List& a = *array;

    a[1] = 64;
    array->display();

    for (u64 i = 0; i < a.size(); i++) {

        LOG((int)a[i])
    }

    return 0;
}
