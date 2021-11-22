#pragma once
#ifndef ORION_ARRAY_H
#define ORION_ARRAY_H

#include"dtype.h"
#include"debug.h"

#define Type se::abs::Type
#define ReturnType se::abs::ReturnType

#ifdef __cplusplus
extern "C++" {

    // pass
    namespace Ex {

        template<typename T>
        class List {

            private:

                struct Node {

                    struct Node *previous;
                    struct Node *next;

                    T value;

                    Node(void) {}
                    ~Node() {}

                };

                struct NodeIterator {

                    Node *begin;
                    Node *end;

                    NodeIterator(void) {}
                    ~NodeIterator() {}
                };

                Node *head;
                Node *midz;
                Node *tail;

                u64 dataCount;

                u64 getMiddlePos(void) {

                    return ((dataCount & 1) == 1 ? (dataCount + 1) / 2 : dataCount / 2) - 1;
                }

                u64 getMiddlePos(u64 m_size) {

                    return ((m_size & 1) == 1 ? (m_size + 1) / 2 : m_size / 2) - 1;
                }

                Node& middleSearchChild(u64 index, u64 m_size, NodeIterator nodeIterator) {

                    Node *node;
                    u64 middle, i;

                    middle = getMiddlePos(m_size);
                    i = 0;

                    if (index <= middle) {

                        node = nodeIterator.begin;

                        while (i <= middle) {

                            if (index == i) break;

                            node = node->next;
                            i++;
                        }
                    } else if (middle < index) {

                        node = nodeIterator.end;
                        i = m_size - 1;

                        while (middle < i) {

                            if (index == i) break;

                            node = node->previous;
                            i--;
                        }
                    }

                    return *node;
                }

                Node& middleSearch(u64 index) {

                    Node *node;
                    NodeIterator nodeIterator;
                    u64 middle, m_size;

                    node = new Node();
                    nodeIterator.begin = head;
                    middle = getMiddlePos();
                    m_size = 0;

                    if (index <= middle) {

                        if (!!(dataCount & 1)) {

                            m_size = middle;

                            if (index < middle) nodeIterator.end = midz->previous;

                            if (middle == index) return midz; 

                        } else {

                            m_size = middle + 1;
                            nodeIterator.end = midz;
                        }

                        node = &middleSearchChild(index, m_size, nodeIterator);

                    } else {

                        nodeIterator.begin = midz->next;
                        nodeIterator.end = tail;

                        node = &middleSearchChild(index - middle - 1, m_size, nodeIterator);
                    }

                    return *node;
                }

                void updateMiddleReduce(void) {

                    u64 vmiddle, middle;

                    vmiddle = getMiddlePos(dataCount - 1);
                    middle = getMiddlePos();

                    if (middle == vmiddle) {

                        midz = midz->next;

                    } else if (vmiddle < middle) {

                        midz = midz->previous;

                    }
                }

                void updateMiddleLeftReduce(void) {

                    u64 vmiddle, middle;

                    vmiddle = getMiddlePos(dataCount - 1);
                    middle = getMiddlePos();

                    if (middle == vmiddle) {

                        midz = midz->next;

                    }
                }

                void updateMiddleRightReduce(void) {

                    u64 vmiddle, middle;

                    vmiddle = getMiddlePos(dataCount - 1);
                    middle = getMiddlePos();

                    if (vmiddle < middle) {

                        midz = midz->previous;

                    }
                }

                void updateMiddleLeftAccrue(void) {

                    u64 vmiddle, middle;

                    vmiddle = getMiddlePos(dataCount + 1);
                    middle = getMiddlePos();

                    if (middle == vmiddle) {

                        midz = midz->previous;
                    }
                }

                void updateMiddleAccrue(void) {

                    updateMiddleLeftAccrue();
                }

                void updateMiddleRightAccrue(void) {

                    u64 vmiddle, middle;

                    vmiddle = getMiddlePos(dataCount + 1);
                    middle = getMiddlePos();

                    if (middle < vmiddle) {

                        midz = midz->next;

                    }
                }

                void omitNode(Node *node) {

                    if (node != tail) node->next->previous = node->previous;
                    else tail = node->previous;
                    
                    if (node != head) node->previous->next = node->next;
                    else head = node->next;

                }

                List& _concat(void) {

                    return *(new List());
                }

                template<typename... Args>
                List& _concat(List& array, Args&&... arguments) {

                    List *copy;
                    Node *node;

                    copy = &(array.copy());
                    node = &(concat(arguments...))->first();

                    while (node != nullptr) {

                        copy->push(node->data);
                        node = node->next;

                    }

                    return *copy;
                }

            // private

            public:

                List(void) {

                    head = nullptr;
                    midz = nullptr;
                    tail = nullptr;

                }
                
                ~List() {}

                void push(T value);

                auto& getitem(T value);

                void setitem(T value);

                u64 size(T value);

                void remove(u64 index) {

                    // assert(index < dataCount);
                    if (!(index < dataCount)) return;

                    Node *node;
                    u64 middle;

                    node = &middleSearch(index);
                    middle = getMiddlePos();

                    if (node == nullptr) return;
                    
                    omitNode(node);

                    if (index < middle) {

                        updateMiddleLeftReduce();

                    } else if (middle == index) {

                        updateMiddleReduce();

                    } else {

                        updateMiddleRightReduce();
                    }

                    free(node);

                    dataCount--;
                }

                List& copy(void);

                template<typename... Args>
                List& concat(Args&&... arguments) {

                    return _concat(*this, arguments...);
                }

                auto& first(void);

                auto& top(void);

                T shift(void);
                
                T pop(void);

                auto& indexOf(T value);

                List& reverse(void);

                bool includes(T value);

                List& slice(u64 start, u64 end);

                void put(u64 index, T value) {

                    Node *node;
                    Node *temp;

                    u64 middle;

                    node = &middleSearch(index);
                    temp = new Node();

                    middle = getMiddlePos();

                    node->data = value;

                    if (index < middle) {


                    } else if (middle == index) {


                    } else {

                        
                    }
                }

                void puts(u64);

                template<typename... Args>
                void puts(u64 index, T value, Args&&... arguments);

                template<typename... Args>
                List& splice(u64 start, u64 deleteCount, Args&&... arguments);

                T& operator[](int index);

            // public
        };

        // Dict
    };
    
    namespace Se {

        template<typename T>
        class List {};
    };

}
#endif

#endif
