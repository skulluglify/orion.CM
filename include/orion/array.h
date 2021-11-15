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
            Node() {}
            ~Node() {}
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

                ui32 get_middle_pos(size_t size) {
                    if ((size & 1) == 1) return (ui32)((size + 1) / 2);
                    return (ui32)(size / 2);
                }

                Node<T> *middle_search_child(uint32_t size, size_t index, NodeDistance<T> *nodeDistance) {
                    Node<T> *node;
                    Node<T> *begin;
                    Node<T> *end;
                    uint32_t middle, i;
                    node = new Node<T>();
                    begin = new Node<T>();
                    end = new Node<T>();
                    begin = nodeDistance->begin;
                    end = nodeDistance->end;
                    middle = get_middle_pos(size) - 1;
                    if (index <= middle) {  // ODD | EVEN AS SAME MEAN
                        node = begin;
                        i = 0;
                        while (i <= middle) {
                            if (index == i) break;
                            node = node->next;
                            i++;
                        }
                    } else if (middle < index) { // ODD | EVEN AS SAME
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

                Node<T> *middle_search(size_t index) {
                    Node<T> *node;
                    NodeDistance<T> *nodeDistance;
                    uint32_t middle, size;
                    node = new Node<T>();
                    nodeDistance = new NodeDistance<T>();
                    middle = get_middle_pos(count) - 1;
                    size = 0;
                    nodeDistance->begin = head; // start | middle as same
                    if (index <= middle) {
                        if ((count & 1) == 1) { // ODD
                            size = middle;
                            if (index < middle) {
                                nodeDistance->end = midz->previous;
                            }
                            if (index == middle) return midz;
                        } else { // EVEN
                            size = middle + 1;
                            nodeDistance->end = midz;
                        }
                        node = middle_search_child(size, index, nodeDistance);
                    } else if (middle < index) { // ODD | EVEN AS SAME
                        nodeDistance->begin = midz->next;
                        nodeDistance->end = tail;
                        node = middle_search_child(size, index - middle - 1, nodeDistance);
                    }
                    return node;
                }

                // ********************** FOR REMOVE FUN ********************** //

                void update_middle_reduce() { // if middle loss

                    ui32 vmiddle = get_middle_pos(count - 1) - 1; // virtual
                    ui32 middle = get_middle_pos(count) - 1;

                    if (vmiddle == middle) {
                        midz = midz->next;
                    }
                    else if (vmiddle == (middle - 1)) {
                        midz = midz->previous;
                    }
                }

                void update_middle_reduce_right() { // if right loss

                    ui32 vmiddle = get_middle_pos(count - 1) - 1; // virtual
                    ui32 middle = get_middle_pos(count) - 1;

                    if (vmiddle == (middle - 1)) {
                        midz = midz->previous;
                    }
                }

                void update_middle_reduce_left() { // if left loss

                    ui32 vmiddle = get_middle_pos(count - 1) - 1; // virtual
                    ui32 middle = get_middle_pos(count) - 1;

                    if (vmiddle == middle) {
                        midz = midz->next;
                    }
                }

                // ********************** FOR REMOVE FUN ********************** //

            public:

                LinkedList() {

                    head = nullptr;
                    midz = nullptr;
                    tail = nullptr;
                    count = 0;
                }
                
                // ~LinkedList() {}

                void push(T data) {
                    Node<T> *node;
                    node = new Node<T>();
                    node->data = data;
                    if (head == nullptr) {
                        head = node;
                        midz = node;
                        tail = node;
                    } else {
                        tail->next = node;
                        node->previous = tail;
                        tail = node; // SWAP
                        if ((count & 1) == 0) {
                            midz = midz->next;
                        }
                    }
                    count++;
                }

                // TODOs
                T get(size_t index) {
                    Node<T> *node;
                    // node = head;
                    if (index < count) {

                        // while (index > 0) {
                            // node = node->next;
                            // index--;
                        // }

                        node = middle_search(index); // 4 virtual abstract

                        if (node != nullptr) return node->data;
                    }
                    return 0;
                }

                void set(size_t index, T data) {
                    Node<T> *node;
                    // node = head;
                    if (index < count) {

                        // while (index > 0) {
                            // node = node->next;
                            // index--;
                        // }

                        node = middle_search(index); // 4 virtual abstract

                        if (node != nullptr) node->data = data;
                    }
                }
                
                // length & middle pos
                size_t size(void) {

                    return count;
                }

                // TODOs
                void remove(size_t index) {
                    Node<T> *node;
                    // node = head;
                    if (index < count) {

                        // while (index > 0) {
                            // node = node->next;
                            // index--;
                        // }

                        node = middle_search(index); // 4 virtual abstract


                        ui32 middle = get_middle_pos(count) - 1;
                        
                        LOG("middle " << middle)

                        if (index == 0) {

                            if (head->next != nullptr) {
                                head = head->next;
                                update_middle_reduce_left();
                                free(head->previous);
                            }

                        }

                        else if (index == (size_t)(middle)) {    

                            Node<T> *displace;
                            displace = midz;
                            if (displace->previous != nullptr && displace->next != nullptr) {
                                update_middle_reduce();
                                displace->next->previous = displace->previous;
                                displace->previous->next = displace->next;
                                free(displace);
                            }
                        }

                        else if (index == (count - 1)) {

                            if (tail->previous != nullptr) {
                                tail = tail->previous;
                                update_middle_reduce_right();
                                free(tail->next);
                            }
                        }

                        else {

                            // random node
                            // update midz if left or right
                            if (index < middle) {

                                node->previous->next = node->next;
                                node->next->previous = node->previous;
                                update_middle_reduce_left();
                                free(node);

                            }
                            else if (middle < index) {

                                node->previous->next = node->next;
                                node->next->previous = node->previous;
                                update_middle_reduce_right();
                                free(node);

                            }
                        }

                        count--;
                    }
                }


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
