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
        class LinkedList {

            private:

                Node<T> *head;
                Node<T> *midz;
                Node<T> *tail;
                
                size_t count;

                ui32 get_middle_pos(size_t n) {

                    ui32 middle;

                    if ((n & 1) == 1) middle = ((n -1) / 2) +1;
                    else middle = n / 2;

                    return middle;
                }

                Node<T>* recursive_middle_search( Node<T> *node, uint32_t countmid, size_t index, size_t length, uint32_t start, bool stop ) {

                    uint32_t middle = get_middle_pos(length);
                    size_t r = middle + start;
                    size_t x = index + 1;

                    // LEFT | CENTER | RIGHT
                    if (length % 2 == 1) {

                        if (x < middle) {

                            // LEFT
                            if (!stop) return recursive_middle_search(node, countmid, index, middle, 0, true);
                            else {

                                if (middle == countmid) node = midz;

                                for (uint32_t i = start; i < r; i++) {

                                    if (index != i) node = node->next;
                                    else break;
                                }
                            }

                        }

                        // OPTIMIZE
                        else if (x == middle) {

                            if (countmid == x) {

                                node = midz;
                            }

                            else {

                                if (middle == countmid) node = midz;

                                for (uint32_t i = start; i < r; i++) {

                                    node = node->next;
                                }
                            }
                        }

                        else if (middle < x) {

                            // RIGHT
                            if (!stop) return recursive_middle_search(node, countmid, index, middle, middle -1, true);
                            else {

                                if (middle == countmid || countmid < r) node = tail;
                                else node = midz;

                                for (int64_t i = r-1; start <= i; i--) {

                                    if (index != (middle + (size_t)(i))) node = node->previous;
                                    else break;
                                }
                            }
                        }

                    } else {

                        if (x <= middle) {

                            // LEFT
                            if (!stop) return recursive_middle_search(node, countmid, index, middle, 0, true);
                            else {

                                if (middle == countmid) node = midz;

                                for (uint32_t i = start; i < r; i++) {

                                    if (index != i) node = node->next;
                                    else break;
                                }
                            }
                        }

                        else if (middle < x) {


                            // RIGHT
                            if (!stop) return recursive_middle_search(node, countmid, index, middle, middle -1, true);
                            else {

                                if (middle == countmid || countmid < r) node = tail;
                                else node = midz;

                                for (int64_t i = r-1; start <= i; i--) {

                                    if (index != (middle + (size_t)(i))) node = node->previous;
                                    else break;
                                }
                            }
                        }
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

                    uint32_t countmid = get_middle_pos(count);

                    // while (index > 0) {

                        // node = node->next;

                        // index--;
                        
                    // }

                    node = recursive_middle_search(node, countmid, index, count, 0, false);

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
