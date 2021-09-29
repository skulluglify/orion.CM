#pragma once
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#ifdef __cplusplus

#include <iostream>

using namespace std;

#define LOG(x) cout << "[DEBUG]: " << x << endl;

template<typename T>
struct MemberList {
    MemberList<T>* before;
    T value;
    MemberList<T>* after;
    MemberList() {}
    ~MemberList() {}
};

// push
// remove
// set
// index
// get
// begin
// end

// concat LinkedList LinkedList
// join LinkedList | list
// to_list

// sort
// reversed

template<typename T, size_t N>
class List {

    private:

        size_t n = 0;

    public:

        List() {};
        ~List() {};

        size_t length = N;
        T* data = new T[N];

        size_t push (T value) {
            if (n < length) {
                data[n] = value;
                return n++;
            }
            return -1;
        }

};

template<typename T>
class LinkedList {

    private:

        MemberList<T>* _begin;
        MemberList<T>* _end;
    
    public:

        LinkedList() {}
        ~LinkedList() {}
        
        size_t length;

        MemberList<T>* create() {
            MemberList<T>* ptrnode = nullptr;
            ptrnode = new MemberList<T>();
            return ptrnode;
        }

        void push(T value) {
            MemberList<T>* ptrnode = create();
            ptrnode->value = (T)(value);
            if (_begin == nullptr) {
                _begin = ptrnode;
            } else {
                ptrnode->before = _end;
                _end->after = ptrnode;
            }
            _end = ptrnode;
            length++;
            // return ptrnode->value;
        }

        void remove(MemberList<T>* ptrnode) {
            if (ptrnode->after != nullptr && ptrnode->before != nullptr) {
                ptrnode->after->before = ptrnode->before;
                ptrnode->before->after = ptrnode->after;
                length--;
            }
            delete ptrnode;
        }

        MemberList<T>* get(size_t i) {
            if (length > i) {
                size_t middle = (size_t)(length / 2);
                if (i <= middle) {
                    MemberList<T>* ptrnode = _begin;
                    while (ptrnode->after != nullptr && i > 0) {
                        ptrnode = ptrnode->after;
                        i--;
                    }
                    return ptrnode;
                } else if (middle < i) {
                    i = length - 1 - i;
                    MemberList<T>* ptrnode = _end;
                    while (ptrnode->before != nullptr && i > 0) {
                        ptrnode = ptrnode->before;
                        i--;
                    }
                    return ptrnode;
                }
            }
            return nullptr;
        }

        size_t index(MemberList<T>* memberlist) {
            size_t i = 0;
            MemberList<T>* ptrnode = _begin;
            while (true) {
                if (ptrnode == memberlist) {
                    return i;
                }
                if (ptrnode == nullptr) break;
                ptrnode = ptrnode->after;
                i++;
            }
            return -1;
        }

        short set(size_t i, T value) {
            if (length > i) {
                size_t middle = (size_t)(length / 2);
                if (i <= middle) {
                    MemberList<T>* ptrnode = _begin;
                    while (ptrnode->after != nullptr && i > 0) {
                        ptrnode = ptrnode->after;
                        i--;
                    }
                    ptrnode->value = (T)(value);
                    return 1;
                } else if (middle < i) {
                    i = length - 1 - i;
                    MemberList<T>* ptrnode = _end;
                    while (ptrnode->before != nullptr && i > 0) {
                        ptrnode = ptrnode->before;
                        i--;
                    }
                    ptrnode->value = (T)(value);
                    return 1;
                } else {
                    return 0;
                }
            }
            return -1;
        }

        void concat() {}

        void join(MemberList<T>* memberlist) {
            (void)memberlist;
        }

        void join(T* memberlist) {
            size_t i = 0;
            while (true) {
                if (!memberlist[i] || 0xFFFFFFFFFFFFFFFF <= i) break;
                push(memberlist[i]);
                i++;
            }
        }

        T* to_list() {
            size_t i = 0;
            T* temp = new T[length];
            MemberList<T>* ptrnode = _begin;
            while (true) {
                if (ptrnode == nullptr || length <= i) break;
                temp[i] = (T)(ptrnode->value);
                ptrnode = ptrnode->after;
                i++;
            }
            return temp;
        }

        void sort() {}

        void reverse() {}

        MemberList<T>* begin() {
            return _begin;
        }

        MemberList<T>* end() {
            return _end;
        }

};

// FEATURES
// middle
// loop / ref
// TREE array, absolute id index

#endif

#endif /*_LINKEDLIST_H_*/
