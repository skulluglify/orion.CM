#include <iostream>
#include "../extras/orion/stack.h"

// queue, stack, array, tree
// sort, reverse, concat

using namespace std;

int main(int argc, const char** argv) {

    (fn)argc;
    (fn)argv;

    LinkedList<int>* e = new LinkedList<int>();

    e->push(8);
    e->push(6);
    e->push(4);
    e->push(2);
    e->push(10);

    LOG(e->length)

    LOG(e->get_ptr(e->find(6))->data)
    LOG(e->get_ptr(e->find(6)))
    LOG(e->get_ptr(e->find(8))->after)
    LOG(e->get_ptr(e->find(4))->before)

    LOG("t1")
    
    LOG(e->get_ptr(e->find(4)))
    LOG(e->get_ptr(e->find(4))->after)
    LOG(e->get_ptr(e->find(2)))
    LOG(e->get_ptr(e->find(2))->before)

    e->remove(6);
    LOG(e->pop())
    LOG(e->shift())

    LOG("t2")

    LOG(e->length)

    // LOG(e->get_ptr(e->find(6))->data)
    LOG(e->find(6))
    LOG(e->get(0))
    // LOG(e->get_ptr(e->find(8))->after)
    LOG(e->get_ptr(e->find(4))->before)

    LOG("t3")
    
    LOG(e->get_ptr(e->find(4)))
    LOG(e->get_ptr(e->find(4))->after)
    LOG(e->get_ptr(e->find(2)))
    LOG(e->get_ptr(e->find(2))->before)

    e->get(100);

    LOG("t4")

    List<int>* l = new List<int>(3);

    l->push(8);
    l->push(7);
    l->push(6);

    LOG(l->data[0])
    LOG(l->data[1])
    LOG(l->data[2])

    LOG(l->length)

    return 0;
}