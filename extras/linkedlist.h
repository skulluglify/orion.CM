#pragma once
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#ifdef __cplusplus

#include <iostream>

using namespace std;

#define LOG(x) cout << x << endl;

template<typename T>
struct MemberList {
	MemberList<T>* before;
	T value;
	MemberList<T>* after;
	MemberList() {}
	~MemberList() {}
};

// add
// remove
// set
// index
// get
// begin
// end

template<typename T>
class LinkedList {

	private:

		MemberList<T>* _begin;
		MemberList<T>* _end;
	
	public:

		LinkedList() {}
		~LinkedList() {}
		
		long int length;

		MemberList<T>* create() {
			MemberList<T>* ptrnode = nullptr;
			ptrnode = new MemberList<T>();
			return ptrnode;
		}

		void add(T value) {
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

		MemberList<T>* get(long int i) {
			if (length > i) {
				long int middle = (long int)(length / 2);
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

		int index(MemberList<T>* memberlist) {
			long int i = 0;
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

		int set(long int i, T value) {
			if (length > i) {
				long int middle = (long int)(length / 2);
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
