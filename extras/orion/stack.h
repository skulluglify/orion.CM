#pragma once
#ifndef _OE_STACK_H_
#define _OE_STACK_H_

#include "typing.h"

#ifdef __cplusplus

template<typename T>
class List {

    private:

        size_t n = 0;

    public:

        T* data = nullptr;
        size_t length = 0;
        
        List(size_t N) {
            data = new T[N];
            length = N;
        };
        
        ~List() {};


        size_t push (T value) {
            data[n] = value;
            return n++;
        }

};

template<typename T>
struct MemberList {

    MemberList<T>() {}
    ~MemberList<T>() {}
    
    MemberList<T>* before;
    
    T data;
    
    MemberList<T>* after;
    
};

template<typename T>
class LinkedList {

    public:

        LinkedList<T> () {}
        ~LinkedList<T> () {}

        size_t length = 0;

    private:

        MemberList<T>* top = nullptr;
        MemberList<T>* bottom = nullptr;
        MemberList<T>* center = nullptr;
        size_t members = 0;
        size_t middle = 0;

    public:

        MemberList<T>* begin() {

            return *top;

        }

        MemberList<T>* end() {


            return *bottom;

        }

        MemberList<T>* next(MemberList<T>* ptrnode) {

            return ptrnode->after;
            
        }

        fn push(T data) {

            MemberList<T>* ptrnode = nullptr;
            ptrnode = new MemberList<T>();
            ptrnode->data = data;

            if (bottom == nullptr) {
                bottom = ptrnode;
                center = bottom;
            }

            if (top != nullptr) {
                top->after = ptrnode;
                ptrnode->before = top;
            }

            size_t m = members / 2;

            if (middle < m) {
                center = center->after;
            }

            middle = m;

            top = ptrnode;

            length = ++members;
            
        }


        MemberList<T>* get_ptr(size_t i) {

            if (members > i) {

                if (i < middle) {

                    //top after
                    MemberList<T>* ptrnode = bottom;
                    while (ptrnode->after != nullptr && i > 0) {

                        ptrnode = ptrnode->after;
                        i--;
                        
                    }

                    return ptrnode;
                    
                    
                } else {

                    //center after
                    i = i - middle;
                    MemberList<T>* ptrnode = center;
                    while (ptrnode->after != nullptr && i > 0) {

                        ptrnode = ptrnode->after;
                        i--;
                        
                    }

                    return ptrnode;

                }
                
            }

            return nullptr;
        }

        T get(size_t i) {

            return get_ptr(i)->data;

        }

        i64 find_ptr(MemberList<T>* memberlist) { // size_t cannot reach -1
            size_t i = 0;
            MemberList<T>* ptrnode = bottom;
            while(ptrnode != nullptr) {
                if (ptrnode == memberlist) 
                    return i;
                ptrnode = ptrnode->after;
                i++;
            }
            return -1;
        }

        i64 find(T data) { // size_t cannot reach -1
            size_t i = 0;
            MemberList<T>* ptrnode = bottom;
            while(ptrnode != nullptr) {
                if (ptrnode->data == data) {
                    return i;
                }
                ptrnode = ptrnode->after;
                i++;
            }
            return -1;
        }

        bool set(size_t i, T data) {

            if (members > i) {

                if (i < middle) {

                    //top after
                    MemberList<T>* ptrnode = bottom;
                    while (ptrnode->after != nullptr && i > 0) {

                        ptrnode = ptrnode->after;
                        i--;
                        
                    }

                    ptrnode->data = data;
                    return 1;
                    
                    
                } else {

                    //center after
                    i = i - middle;
                    MemberList<T>* ptrnode = center;
                    while (ptrnode->after != nullptr && i > 0) {

                        ptrnode = ptrnode->after;
                        i--;
                        
                    }

                    ptrnode->data = data;
                    return 1;

                }
                
            }

            return 0;
        }

        bool remove_ptr(MemberList<T>* memberlist) {

            MemberList<T>* ptrnode = bottom;
            while(ptrnode != nullptr) {
                if (ptrnode == memberlist) {
                    if (ptrnode->before != nullptr) {
                        ptrnode->before->after = ptrnode->after;
                    }
                    if (ptrnode->after != nullptr) {
                        ptrnode->after->before = ptrnode->before;
                    }
                    if (ptrnode == top) {
                        top = ptrnode->before;
                        top->after = nullptr;
                    }
                    if (ptrnode == bottom) {
                        bottom = ptrnode->after;
                        bottom->before = nullptr;
                    }
                    length = --members;
                    size_t m = members / 2;
                    if (middle > m) {
                        center = center->before;
                        middle = m;
                    }
                    // free(ptrnode);
                    return 1;
                }
                ptrnode = ptrnode->after;
            }
    
            return 0;
        }

        bool remove(T data) {

            MemberList<T>* ptrnode = bottom;
            while(ptrnode != nullptr) {
                if (ptrnode->data == data) {
                    if (ptrnode->before != nullptr) {
                        ptrnode->before->after = ptrnode->after;
                    }
                    if (ptrnode->after != nullptr) {
                        ptrnode->after->before = ptrnode->before;
                    }
                    if (ptrnode == top) {
                        top = ptrnode->before;
                        top->after = nullptr;
                    }
                    if (ptrnode == bottom) {
                        bottom = ptrnode->after;
                        bottom->before = nullptr;
                    }
                    length = --members;
                    size_t m = members / 2;
                    if (middle > m) {
                        center = center->before;
                        middle = m;
                    }
                    // free(ptrnode);
                    return 1;
                }
                ptrnode = ptrnode->after;
            }
    
            return 0;
        }

        // splice
        // slice
        // reverse
        // join
        // concat
        // sort

        T pop() {
            T data = top->data;
            remove_ptr(top);
            return data;
        }

        T shift() {
            T data = bottom->data;
            remove_ptr(bottom);
            return data;
        }
        
};

#endif

#endif /*_OE_STACK_H_*/