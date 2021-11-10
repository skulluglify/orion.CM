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

                ui32 get_middle_pos(void) {

                    ui32 middle;

                    if (count & 1 == 1) middle = ((count -1) / 2) +1;
                    else middle = count / 2;

                    return middle;
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
                        // if (count & 1 == 1) middle = (count -1) / 2;
                        // else middle = count / 2;
                        // midz = getPtr(middle);
                        if (count % 2 == 0) {

                            midz = midz->next;
                        }

                    }

                    count++;
                }

                // TODOs
                T get(size_t index) {

                    Node<T> *node;
                    uint32_t middle;

                    node = head;

                    // while (index > 0) {

                        // node = node->next;

                        // index--;
                        
                    // }

                    middle = get_middle_pos();

                    // count % 2 == 0, <= middle, middle < | default
                    // count % 2 > 0, < middle, middle <=

                    if (middle > 0) {

                        // middle > 0
                        // size > 1
                        // index available > 0
                        if (index <= middle) {

                            // middle / 2 
                            // 0 - x - middle
                            // can cut off two position bcs have previous, and next
                            
                        } else 
                        if (middle < index) {

                            // middle / 2 
                            // middle - x - last
                            // can cut off two position bcs have previous, and next
                            
                        }
                        
                    }
                    else {

                        // middle == 0
                        // size 1
                        // index available 0
                        if (index != 0) return 0;
                        
                    }

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
