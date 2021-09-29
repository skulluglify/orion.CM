#include <iostream>
#include "linkedlist.h"

using namespace std;

int main(int argc, const char** argv) {

    (void)argc;
    (void)argv;

    LinkedList<int> *a = nullptr;
    a = new LinkedList<int>();

    a->push(255);
    a->push(24);
    a->push(3);

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

    int* f = a->to_list();

    a->join(f);
    a->join(f);

    cout << 88 << endl;

    cout << a->length << endl;

    auto* m = new List<int, 3>();
    m->push(24);

    cout << m->data[0] << endl;
    if (!m->data[3]) {
        cout << "owk wanna be laugh" << endl;
    }

    cout << 55 << endl;

    return 0;
}
