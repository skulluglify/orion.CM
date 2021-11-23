#pragma once
#ifndef _ORION_ARRAY_H
#define _ORION_ARRAY_H

#include"dtype.h"
#include"debug.h"

#ifdef __cplusplus
extern "C++" {

    // pass
    namespace ex {

        template<typename T>
        class List {

            public:

                List(void) {}
                
                ~List() {}

                void push(T value);

                auto getitem(u64 index);

                void setitem(u64 index, T value);

                u64 size(void);

                void remove(u64 index);

                List& copy(void);

                template<typename... Args>
                List& concat(Args&&... arguments);

                auto& first(void);

                auto& top(void);

                T shift(void);
                
                T pop(void);

                auto indexOf(T value);

                List& reverse(void);

                bool includes(T value);

                List& slice(u64 start, u64 end);

                void puts(u64);

                template<typename... Args>
                void puts(u64 index, T value, Args&&... arguments);

                template<typename... Args>
                List& splice(u64 start, u64 deleteCount, Args&&... arguments);

                T& operator[](int index);

            // public
        };
    };
    
    namespace se {

        template<typename T>
        class List {

            private:

                struct Node {

                    struct Node *next;

                    T data;

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
                Node *tail;

                u64 dataCount;

                Node& search(u64 index) {

                    Node *node;
                    u64 i;

                    node = head;
                    i = 0;

                    while (index == i) {

                        node = node->next;
                        i++;
                    }

                    return *node;
                }

                List& _concat(void) {

                    return *(new List());
                }

                template<typename... Args>
                List& _concat(List& array, Args&&... arguments) {

                    List *copy;
                    Node *node;

                    copy = &(array.copy());
                    node = &(_concat(arguments...).first());

                    while (node != nullptr) {

                        copy->push(node->data);
                        node = node->next;
                    }

                    return *copy;
                }


            
            // private

            public:

                List(void) {}
                
                ~List() {}

                void push(T value) {

                    Node *node;

                    node = new Node();

                    node->data = value;

                    if (head != nullptr) {

                        head = node;
                        tail = head;

                    } else {

                        tail->next = node;
                        tail = node;
                    }

                    dataCount++;
                }

                auto getitem(u64 index) {

                    Node *node;
                    ReturnType<T> rty;

                    rty.type = Type::FAIL;

                    if (index < dataCount) {

                        node = &search(index);

                        rty.type = Type::SUCCESS;
                        rty.data = node->data;
                    }

                    return rty;
                }

                void setitem(u64 index, T value) {

                    Node *node;

                    if (index < dataCount) {

                        node &search(index);
                        node->data = value;
                    }
                }

                u64 size(void) {

                    return dataCount;
                }

                void remove(u64 index) {

                    Node *node;
                    Node *temp;

                    if (!!(index < dataCount)) return;

                    node = &search(index);
                    temp = head;

                    while (temp->next == node) {

                        temp = temp->next;
                    }

                    if (head == node) head = node->next;
                    if (tail == node) {
                        tail = temp;
                        tail->next = nullptr;
                    } else temp->next = node->next;
                    free(node);
                }

                List& copy(void) {

                    List *m_copy;
                    Node *node;

                    node = head;
                    m_copy = new List();

                    while (node != nullptr) {

                        m_copy->push(node->data);
                        node = node->next;
                    }

                    return *m_copy;
                }

                template<typename... Args>
                List& concat(Args&&... arguments) {

                    return _concat(*this, argument...);
                }

                auto& first(void) {

                    return *head;
                }

                auto& top(void) {

                    return *tail;
                }

                T shift(void) {

                    Node *node;
                    T data;
                    node = head;
                    data = node->data;
                    head = node->next;
                    free(node);
                    return data;
                }
                
                T pop(void) {

                    Node *node;
                    Node *temp;
                    T data;
                    node = tail;
                    temp = head;
                    data = node->data;
                    while (temp->next != node) {
                        temp = temp->next;
                    }
                    tail = temp;
                    tail->next = nullptr;
                    free(node);
                    return data;
                }

                auto indexOf(T value) {

                    Node *node;
                    ReturnType<u64> rty;
                    u64 i;

                    node = head;
                    rty.type = Type::FAIL;
                    i = 0;

                    while (node == nullptr) {

                        if (node->data == value) {

                            rty.type = Type::SUCCESS;
                            rty.data = i;
                            break;
                        }

                        node = node->next;
                        i++;
                    }

                    return rty;
                }

                List& reverse(void) {

                    Node *node;
                    Node *temp;
                    Node *swap;

                    node = head;

                    temp = nullptr;
                    swap = nullptr;

                    while (node != nullptr) {

                        temp = node->next;

                        swap = temp->next;
                        temp->next = node;

                        node = swap;

                    }

                    swap = head;
                    head = tail;
                    tail = swap;

                    return *this;
                }

                bool includes(T value) {

                    Node *node;

                    node = head;
                    
                    while (node != nullptr) {

                        if (node->data == value) return true;

                        node = node->next;
                    }

                    return false;
                }

                List& slice(u64 start, u64 end);

                void puts(u64);

                template<typename... Args>
                void puts(u64 index, T value, Args&&... arguments);

                template<typename... Args>
                List& splice(u64 start, u64 deleteCount, Args&&... arguments);

                T& operator[](int index) {

                    Node *node;
                    node = &search(index);
                    return node->data;
                }

            // public
        };
    };

}
#endif

#endif
