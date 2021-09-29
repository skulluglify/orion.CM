#include <iostream>
#include "linkedlist.h"

using namespace std;

int main(int argc, const char** argv) {

    (void)argc;
    (void)argv;

    LinkedList<int> *a = nullptr;
    a = new LinkedList<int>();

    a->add(255);
    a->add(24);
    a->add(3);

    cout << a->end()->value << endl;
    cout << a->begin()->value << endl;

    a->set(2, 64);

    MemberList<int>* b = a->get(2);
    cout << b->value << endl;

    cout << a->length << endl;

    a->remove(a->get(1));

    cout << a->length << endl;

    MemberList<int>* c = a->get(0);
    cout << c->value << endl;

    MemberList<int>* d = a->get(1);
    cout << d->value << endl;

    MemberList<int>* e = a->get(0);
    cout << a->index(e) << endl;

    cout << 55 << endl;

    return 0;
}