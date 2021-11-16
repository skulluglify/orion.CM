#pragma once
#ifndef __ORION_ARRAY__
#define __ORION_ARRAY__

#include<string>
#include"dtype.h"
#include"debug.h"

#ifdef __cplusplus

extern "C++" {


    namespace Ex {

        template<typename T>
        struct ReturnType {

            std::string type;
            T value;

        };

        template<typename T>
        class List {

            private:

                struct Node {
                    
                    struct Node* previous;
                    struct Node* next;
                    
                    T data;

                    // constructor 
                    Node() {}
                    ~Node() {}
                };

                struct NodeIterator { // virtual, and not real case
                    
                    Node* begin;
                    Node* end;

                    // constructor 
                    NodeIterator() {}
                    ~NodeIterator() {}
                };

                Node* head;
                Node* midz;
                Node* tail;
                
                size_t count;

                size_t get_middle_pos(size_t size) {
                    return (size & 1) == 1 ? (size + 1) / 2 : size / 2;
                }

                Node* middle_search_child(uint32_t size, size_t index, NodeIterator nodeIterator) {
                    Node* node;
                    Node* begin;
                    Node* end;
                    uint32_t middle, i;
                    node = new Node();
                    begin = new Node();
                    end = new Node();
                    begin = nodeIterator.begin;
                    end = nodeIterator.end;
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

                Node* middle_search(size_t index) {
                    Node* node;
                    NodeIterator nodeIterator;
                    uint32_t middle, size;
                    node = new Node();
                    middle = get_middle_pos(count) - 1;
                    size = 0;
                    nodeIterator.begin = head; // start | middle as same
                    if (index <= middle) {
                        if ((count & 1) == 1) { // ODD
                            size = middle;
                            if (index < middle) {
                                nodeIterator.end = midz->previous;
                            }
                            if (index == middle) return midz;
                        } else { // EVEN
                            size = middle + 1;
                            nodeIterator.end = midz;
                        }
                        node = middle_search_child(size, index, nodeIterator);
                    } else if (middle < index) { // ODD | EVEN AS SAME
                        nodeIterator.begin = midz->next;
                        nodeIterator.end = tail;
                        node = middle_search_child(size, index - middle - 1, nodeIterator);
                    }
                    return node;
                }

                // ********************** FOR REMOVE FUN ********************** //

                void update_middle_reduce() { // if middle loss

                    size_t vmiddle = get_middle_pos(count - 1) - 1; // virtual
                    size_t middle = get_middle_pos(count) - 1;

                    if (vmiddle == middle) {
                        midz = midz->next;
                    }
                    else if (vmiddle == (middle - 1)) {
                        midz = midz->previous;
                    }
                }

                void update_middle_reduce_right() { // if right loss

                    size_t vmiddle = get_middle_pos(count - 1) - 1; // virtual
                    size_t middle = get_middle_pos(count) - 1;

                    if (vmiddle == (middle - 1)) {
                        midz = midz->previous;
                    }
                }

                void update_middle_reduce_left() { // if left loss

                    size_t vmiddle = get_middle_pos(count - 1) - 1; // virtual
                    size_t middle = get_middle_pos(count) - 1;

                    if (vmiddle == middle) {
                        midz = midz->next;
                    }
                }

                // ********************** FOR REMOVE FUN ********************** //

            public:

                List() {

                    head = nullptr;
                    midz = nullptr;
                    tail = nullptr;
                    count = 0;
                }
                
                // ~List() {}

                void push(T data) {
                    Node* node;
                    node = new Node();
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
                ReturnType<T> get(size_t index) {
                    
                    Node* node;
                    ReturnType<T> returnType;
                    // node = head;
                    if (index < count) {

                        // while (index > 0) {
                            // node = node->next;
                            // index--;
                        // }

                        node = middle_search(index); // 4 virtual abstract

                        if (node != nullptr) {
                            returnType.type = "ok";
                            returnType.value = node->data;
                            return returnType;
                        };
                    }
                    returnType.type = "err";
                    return returnType;
                }

                void set(size_t index, T data) {
                    Node* node;
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
                    Node* node;
                    // node = head;
                    if (index < count) {

                        // while (index > 0) {
                            // node = node->next;
                            // index--;
                        // }

                        node = middle_search(index); // 4 virtual abstract


                        size_t middle = get_middle_pos(count) - 1;
                        
                        // LOG("middle " << middle)

                        // head as same shift
                        // ======================================================
                        if (index == 0) {

                            if (head->next != nullptr) {
                                head = head->next;
                                update_middle_reduce_left();
                                free(head->previous);
                            }

                        }
                        // ======================================================

                        // middle
                        // ======================================================
                        else if (index == (size_t)(middle)) {    

                            Node* displace;
                            displace = midz;
                            if (displace->previous != nullptr && displace->next != nullptr) {
                                update_middle_reduce();
                                displace->next->previous = displace->previous;
                                displace->previous->next = displace->next;
                                free(displace);
                            }
                        }
                        // ======================================================

                        // tail as same pop
                        // ======================================================
                        else if (index == (count - 1)) {

                            if (tail->previous != nullptr) {
                                tail = tail->previous;
                                update_middle_reduce_right();
                                free(tail->next);
                            }
                        }
                        // ======================================================

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

                // copy
                List* copy() {

                    Node* node;
                    List* arrayCopy;
                    
                    node = head;
                    arrayCopy = new List();

                    while (node != nullptr) {

                        arrayCopy->push(node->data);

                        node = node->next;
                    }

                    return arrayCopy;
                }

                List* concat(List* A, List* B) {

                    Node* node;
                    List* arrayCopy;

                    node = &B->bottom();
                    arrayCopy = A->copy();

                    while (node != nullptr) {

                        arrayCopy->push(node->data);

                        node = node->next;
                    }

                    return arrayCopy;
                }

                Node& bottom() {

                    return *head;
                }

                Node& top() {

                    return *tail;
                }

                T shift() {

                    T data;
                    Node* node;

                    node = head;
                    data = node->data;
                    head = node->next;
                    head->previous = nullptr;

                    update_middle_reduce_left();

                    free(node);

                    count--;

                    return data;
                }

                T pop() {

                    T data;
                    Node* node;
                    
                    node = tail;
                    data = node->data;
                    tail = node->previous;
                    tail->next = nullptr;

                    update_middle_reduce_right();

                    free(node);

                    count--;

                    return data;
                }

                ReturnType<size_t> indexOf(T data) {

                    size_t index;
                    Node* node;
                    ReturnType<size_t> returnType;

                    index = 0;
                    node = head;
                    while (node != nullptr) {

                        if (node->data == data) {

                            returnType.type = "ok";
                            returnType.value = index;
                        }

                        node = node->next;
                        index++;
                    }

                    returnType.type = "ok";

                    return returnType;
                }

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
