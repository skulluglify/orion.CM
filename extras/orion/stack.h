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

        MemberList<T>* _top = nullptr;
        MemberList<T>* _bottom = nullptr;
        MemberList<T>* _center = nullptr;
        size_t _members = 0;
        size_t _middle = 0;

    public:

        MemberList<T>* begin() {

            return *_top;

        }

        MemberList<T>* end() {


            return *_bottom;

        }

        MemberList<T>* next(MemberList<T>* ptrnode) {

            return ptrnode->after;
            
        }

        fn push(T data) {

            MemberList<T>* ptrnode = nullptr;
            ptrnode = new MemberList<T>();
            ptrnode->data = data;

            if (_bottom == nullptr) {
                _bottom = ptrnode;
                _center = _bottom;
            }

            if (_top != nullptr) {
                _top->after = ptrnode;
                ptrnode->before = _top;
            }

            size_t m = _members / 2;

            if (_middle < m) {
                _center = _center->after;
            }

            _middle = m;

            _top = ptrnode;

            length = ++_members;
            
        }

        // Queue
        fn enqueue(T data) {
            return push(data);
        }


        MemberList<T>* get_ptr(size_t i) {

            if (_members > i) {

                if (i < _middle) {

                    //_top after
                    MemberList<T>* ptrnode = _bottom;
                    while (ptrnode->after != nullptr && i > 0) {

                        ptrnode = ptrnode->after;
                        i--;
                        
                    }

                    return ptrnode;
                    
                    
                } else {

                    //_center after
                    i = i - _middle;
                    MemberList<T>* ptrnode = _center;
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
            MemberList<T>* ptrnode = _bottom;
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
            MemberList<T>* ptrnode = _bottom;
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

            if (_members > i) {

                if (i < _middle) {

                    //_top after
                    MemberList<T>* ptrnode = _bottom;
                    while (ptrnode->after != nullptr && i > 0) {

                        ptrnode = ptrnode->after;
                        i--;
                        
                    }

                    ptrnode->data = data;
                    return 1;
                    
                    
                } else {

                    //_center after
                    i = i - _middle;
                    MemberList<T>* ptrnode = _center;
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

            MemberList<T>* ptrnode = _bottom;
            while(ptrnode != nullptr) {
                if (ptrnode == memberlist) {
                    if (ptrnode->before != nullptr) {
                        ptrnode->before->after = ptrnode->after;
                    }
                    if (ptrnode->after != nullptr) {
                        ptrnode->after->before = ptrnode->before;
                    }
                    if (ptrnode == _top) {
                        _top = ptrnode->before;
                        _top->after = nullptr;
                    }
                    if (ptrnode == _bottom) {
                        _bottom = ptrnode->after;
                        _bottom->before = nullptr;
                    }
                    length = --_members;
                    size_t m = _members / 2;
                    if (_middle > m) {
                        _center = _center->before;
                        _middle = m;
                    }
                    // free(ptrnode);
                    return 1;
                }
                ptrnode = ptrnode->after;
            }
    
            return 0;
        }

        bool remove(T data) {

            MemberList<T>* ptrnode = _bottom;
            while(ptrnode != nullptr) {
                if (ptrnode->data == data) {
                    if (ptrnode->before != nullptr) {
                        ptrnode->before->after = ptrnode->after;
                    }
                    if (ptrnode->after != nullptr) {
                        ptrnode->after->before = ptrnode->before;
                    }
                    if (ptrnode == _top) {
                        _top = ptrnode->before;
                        _top->after = nullptr;
                    }
                    if (ptrnode == _bottom) {
                        _bottom = ptrnode->after;
                        _bottom->before = nullptr;
                    }
                    length = --_members;
                    size_t m = _members / 2;
                    if (_middle > m) {
                        _center = _center->before;
                        _middle = m;
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
            T data = _top->data;
            remove_ptr(_top);
            return data;
        }

        T shift() {
            T data = _bottom->data;
            remove_ptr(_bottom);
            return data;
        }

        // Stack
        T top() {
        	return _top->data;
        }        

        // Queue
        T dequeue() {
        	return shift();
        }
        
};

#endif

#endif /*_OE_STACK_H_*/
