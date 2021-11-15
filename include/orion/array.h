#pragma once
#ifndef __ORION_ARRAY__
#define __ORION_ARRAY__

#include"dtype.h"
#include"debug.h"

#ifdef __cplusplus

extern "C++" {

    namespace Yo {

        template<typename T>
        struct Node {
            struct Node *previous; T data; struct Node *next;
        };

        template<typename T>
        struct NodeDistance {
            Node<T> *begin; Node<T> *end;
            NodeDistance() {}
            ~NodeDistance() {}
        };

        template<typename T>
        class LinkedList {

            private:

                Node<T> *head;
                Node<T> *midz;
                Node<T> *tail;
                
                size_t count;

                ui32 get_middle_pos(size_t n) {

                    ui32 middle;

                    if ((n & 1) == 1) middle = (n +1) / 2;
                    else middle = n / 2;

                    return middle;
                }

                Node<T> *middle_search_child(uint32_t size, size_t index, NodeDistance<T> *nodeDistance ) {
                    Node<T> *node;
                    Node<T> *begin;
                    Node<T> *end;
                    node = new Node<T>();
                    begin = new Node<T>();
                    end = new Node<T>();
                    begin = nodeDistance->begin;
                    end = nodeDistance->end;
                    uint32_t middle, i;
                    middle = get_middle_pos(size) - 1;
                    if ((size & 1) == 1) {
                        if (index < middle) {
                            node = begin;
                            i = 0;
                            while (i < middle) {
                                if (index == i) break;
                                node = node->next;
                                i++;
                            }
                        }
                        if (index == middle) {
                            node = begin;
                            i = 0;
                            while (!(i == middle)) {
                                node = node->next;
                                i++;
                            }
                        }
                    } else {
                        if (index <= middle) {
                            node = begin;
                            i = 0;
                            while (i <= middle) {
                                if (index == i) break;
                                node = node->next;
                                i++;
                            }
                        }
                    }
                    if (middle < index) {
                        node = end;
                        i = size - 1;
                        while (middle < i) {
                            if (index == i) break;
                            node = node->previous;
                            i--;
                        }
                    }
                    return node;
                }

                Node<T> *middle_search( size_t index ) {
                    Node<T> *node;
                    NodeDistance<T> *nodeDistance;
                    node = new Node<T>();
                    nodeDistance = new NodeDistance<T>();
                    uint32_t middle, size;
                    middle = get_middle_pos(count) - 1;
                    if ((count & 1) == 1) {
                        size = middle;
                        if (index < middle) {
                            nodeDistance->begin = head;
                            nodeDistance->end = midz->previous;
                            node = middle_search_child(size, index, nodeDistance);
                        }
                        if (index == middle) {
                            node = midz;
                        }
                    } else {
                        size = middle + 1;
                        if (index <= middle) {
                            nodeDistance->begin = head;
                            nodeDistance->end = midz;
                            node = middle_search_child(size, index, nodeDistance);
                        }
                    }
                    if (middle < index) {
                        nodeDistance->begin = midz->next;
                        nodeDistance->end = tail;
                        node = middle_search_child(size, index - middle - 1, nodeDistance);
                    }
                    return node;
                }

            public:

                LinkedList<T>() {

                    head = nullptr;
                    midz = nullptr;
                    tail = nullptr;
                    count = 0;
                }
                
                // ~LinkedList<T>() {}

                // push
                void push(T data) {

                    LOG((int)data)

                    Node<T> *node;
                    node = new Node<T>();
                    // uint32_t middle;
                    
                    node->data = data;

                    if (head == nullptr) {

                        head = node;
                        midz = node;
                        tail = node;

                    } else {

                        tail->next = node;
                        node->previous = tail;
                        tail = node;

                        // update midz
                        if (count % 2 == 0) {

                            midz = midz->next;

                        }

                    }

                    count++;
                }

                // TODOs
                T get(size_t index) {

                    Node<T> *node;

                    node = head;

                    // while (index > 0) {

                        // node = node->next;

                        // index--;
                        
                    // }

                    node = middle_search(index);
                    // middle_search(node, index, count, 0, false);

                    if (node != nullptr) return node->data;

                    return 0;
                }
                
                // length & middle pos
                size_t size(void) {

                    return count;
                }

                // TODOs
                // remove
                // concat
                // pop
                // shift
                // indexOf
                // slice
                // splic
                // put | put ( index, value ) | menyisipkan value
        };

    };

}

#endif
#endif
