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

            enum Status {
                FAIL = 0x00,
                OK = 0x01
            };

            ui8 type;
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
                
                ui64 count;

                ui64 GetMiddlePos(ui64 Size) {
                    return (Size & 1) == 1 ? (Size + 1) / 2 : Size / 2;
                }

                Node* MiddleSearchChild(ui64 Size, ui64 index, NodeIterator nodeIterator) {
                    Node* node;
                    Node* begin;
                    Node* end;
                    ui64 middle, i;
                    node = new Node();
                    begin = new Node();
                    end = new Node();
                    begin = nodeIterator.begin;
                    end = nodeIterator.end;
                    middle = GetMiddlePos(Size) - 1;
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
                        i = Size - 1;
                        while (middle < i) {
                            if (index == i) break;
                            node = node->previous;
                            i--;
                        }
                    }
                    return node;
                }

                Node* MiddleSearch(ui64 index) {
                    Node* node;
                    NodeIterator nodeIterator;
                    ui64 middle, Size;
                    node = new Node();
                    middle = GetMiddlePos(count) - 1;
                    Size = 0;
                    nodeIterator.begin = head; // start | middle as same
                    if (index <= middle) {
                        if ((count & 1) == 1) { // ODD
                            Size = middle;
                            if (index < middle) {
                                nodeIterator.end = midz->previous;
                            }
                            if (index == middle) return midz;
                        } else { // EVEN
                            Size = middle + 1;
                            nodeIterator.end = midz;
                        }
                        node = MiddleSearchChild(Size, index, nodeIterator);
                    } else if (middle < index) { // ODD | EVEN AS SAME
                        nodeIterator.begin = midz->next;
                        nodeIterator.end = tail;
                        node = MiddleSearchChild(Size, index - middle - 1, nodeIterator);
                    }
                    return node;
                }

                // ********************** FOR REMOVE FUN ********************** //

                void UpdateMiddleReduce() { // if middle loss

                    ui64 vmiddle = GetMiddlePos(count - 1) - 1; // virtual
                    ui64 middle = GetMiddlePos(count) - 1;

                    if (vmiddle == middle) {
                        midz = midz->next;
                    }
                    else if (vmiddle == (middle - 1)) {
                        midz = midz->previous;
                    }
                }

                void UpdateMiddleReduceRight() { // if right loss

                    ui64 vmiddle = GetMiddlePos(count - 1) - 1; // virtual
                    ui64 middle = GetMiddlePos(count) - 1;

                    if (vmiddle == (middle - 1)) {
                        midz = midz->previous;
                    }
                }

                void UpdateMiddleReduceLeft() { // if left loss

                    ui64 vmiddle = GetMiddlePos(count - 1) - 1; // virtual
                    ui64 middle = GetMiddlePos(count) - 1;

                    if (vmiddle == middle) {
                        midz = midz->next;
                    }
                }

                // ********************** FOR REMOVE FUN ********************** //

                List& ConcatConceptMultiply(void) {

                    return *(new List());
                }

                template<typename... Args>
                List& ConcatConceptMultiply(List& current, Args&&... arguments) {

                    List* arrayCopy;
                    List* arraySafe; // but not safe anymore

                    arrayCopy = &(current.Copy());
                    arraySafe = &ConcatConceptMultiply(arguments...);

                    // for (ui64 i = 0; i < arraySafe->Size(); i++) {

                    //     ReturnType<T> returnType;
                    //     returnType = arraySafe->GetItem(i);

                    //     if (returnType.type == returnType.OK)
                    //         arrayCopy->Push(returnType.value);
                    
                    // }

                    Node* node;
                    node = &arraySafe->Bottom();

                    while (node != nullptr) {

                        arrayCopy->Push(node->data);

                        node = node->next;
                    }

                    return *arrayCopy;
                }

            public:

                List() {

                    head = nullptr;
                    midz = nullptr;
                    tail = nullptr;
                    count = 0;
                }
                
                // ~List() {}

                void Push(T data) {
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
                ReturnType<T> GetItem(ui64 index) {
                    
                    Node* node;
                    ReturnType<T> returnType;
                    // node = head;
                    if (index < count) {

                        // while (index > 0) {
                            // node = node->next;
                            // index--;
                        // }

                        node = MiddleSearch(index); // 4 virtual abstract

                        if (node != nullptr) {
                            returnType.type = returnType.OK;
                            returnType.value = node->data;
                            return returnType;
                        };
                    }

                    returnType.type = returnType.FAIL;
                    
                    return returnType;
                }

                void SetItem(ui64 index, T data) {
                    Node* node;
                    // node = head;
                    if (index < count) {

                        // while (index > 0) {
                            // node = node->next;
                            // index--;
                        // }

                        node = MiddleSearch(index); // 4 virtual abstract

                        if (node != nullptr) node->data = data;
                    }
                }
                
                // length & middle pos
                ui64 Size(void) {

                    return count;
                }

                // TODOs
                void Remove(ui64 index) {
                    
                    Node* node;
                    ui64 last;
                    last = count -1;
                    // node = head;
                    if (index < count) {

                        // while (index > 0) {
                            // node = node->next;
                            // index--;
                        // }

                        node = MiddleSearch(index); // 4 virtual abstract


                        ui64 middle = GetMiddlePos(count) - 1;
                        
                        // LOG("middle " << middle)

                        // head as same Shift
                        // ======================================================
                        if (index == 0) {

                            if (head->next != nullptr) {
                                head = head->next;
                                UpdateMiddleReduceLeft();
                                free(head->previous);
                            }

                        }
                        // ======================================================

                        // middle
                        // ======================================================
                        else if (index == middle) {    

                            Node* displace;
                            displace = midz;
                            if (displace->previous != nullptr && displace->next != nullptr) {
                                UpdateMiddleReduce();
                                displace->next->previous = displace->previous;
                                displace->previous->next = displace->next;
                                free(displace);
                            }
                        }
                        // ======================================================

                        // tail as same Pop
                        // ======================================================
                        else if (index == last) {

                            if (tail->previous != nullptr) {
                                tail = tail->previous;
                                UpdateMiddleReduceRight();
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
                                UpdateMiddleReduceLeft();
                                free(node);

                            }
                            else if (middle < index) {

                                node->previous->next = node->next;
                                node->next->previous = node->previous;
                                UpdateMiddleReduceRight();
                                free(node);

                            }
                        }

                        count--;
                    }
                }

                // Copy
                List& Copy() {

                    Node* node;
                    List* arrayCopy;
                    
                    node = head;
                    arrayCopy = new List();

                    while (node != nullptr) {

                        arrayCopy->Push(node->data);

                        node = node->next;
                    }

                    return *arrayCopy;
                }

                // List& Concat(List* A, List* B) {

                //     Node* node;
                //     List* arrayCopy;

                //     node = &B->Bottom();
                //     arrayCopy = &A->Copy();

                //     while (node != nullptr) {

                //         arrayCopy->Push(node->data);

                //         node = node->next;
                //     }

                //     return *arrayCopy;
                // }

                template<typename... Args>
                List& Concat(Args&&... arguments) {

                    return ConcatConceptMultiply(arguments...);
                }

                Node& Bottom() {

                    return *head;
                }

                Node& Top() {

                    return *tail;
                }

                T Shift() {

                    T data;
                    Node* node;

                    node = head;
                    data = node->data;
                    head = node->next;
                    head->previous = nullptr;

                    UpdateMiddleReduceLeft();

                    free(node);

                    count--;

                    return data;
                }

                T Pop() {

                    T data;
                    Node* node;
                    
                    node = tail;
                    data = node->data;
                    tail = node->previous;
                    tail->next = nullptr;

                    UpdateMiddleReduceRight();

                    free(node);

                    count--;

                    return data;
                }

                ReturnType<ui64> GetIndexOf(T data) {

                    ui64 index;
                    Node* node;
                    ReturnType<ui64> returnType;

                    index = 0;
                    node = head;
                    while (node != nullptr) {

                        if (node->data == data) {

                            returnType.type = returnType.OK;
                            returnType.value = index;
                        }

                        node = node->next;
                        index++;
                    }

                    returnType.type = returnType.FAIL;

                    return returnType;
                }

                void Reverse() {

                    Node* node;
                    Node* safe;
                    Node* Copy;
                    Node* prev;
                    Node* swap;

                    safe = head;
                    Copy = head;
                    node = nullptr;
                    prev = nullptr;
                    swap = nullptr;

                    while (true) {

                        prev = Copy;
                        node = prev->next;

                        // LOG("check at: " << (int)prev->data)

                        if (node == nullptr) break;

                        safe = node->next;
                        Copy = safe;

                        node->next = prev;
                        node->previous = safe;
                        
                        swap = prev->next;
                        prev->next = prev->previous;
                        prev->previous = swap;
                    }

                    swap = head;
                    head = tail;
                    tail = swap;

                    if ((count & 1) == 0) midz = midz->previous;

                    head->next = head->previous;
                    head->previous = nullptr;
                    tail->previous = tail->next;
                    tail->next = nullptr;
                }

                // multiply arguments, fold, variadic
                bool Contains(T data) {

                    Node* node;
                    node = head;

                    while(node != nullptr) {

                        if (node->data == data) return true;

                        node = node->next;
                    }

                    return false;
                }

                // slice (index)start, (count)end+1 start - (length-start)
                List& Slice(ui64 start, ui64 end) {

                    List* copy;
                    Node* safe;
                    Node* node;

                    ui64 middle;
                    ui64 range;
                    ui64 last;
                    
                    copy = new List();
                    safe = nullptr;
                    node = nullptr;

                    middle = GetMiddlePos(count) - 1;
                    range = 0;
                    last = count > 0 ? count - 1 : 0;

                    // if (start < 0) start = 0;
                    if (count < end) end = count;

                    if (start < end) {

                        range = end - start + 1;

                        // while (start != 0) {

                        //     node = node->next;
                            
                        //     start--;
                        // }

                        safe = MiddleSearch(start);

                        while (range != 0) {

                            node = safe;

                            copy->Push(node->data);
                            
                            safe = node->next;

                            // remove node in List
                            if (start == 0) {
                                head = node->next;
                                UpdateMiddleReduceLeft();
                                free(node);
                            }

                            else if (0 < start && start < middle) {
                                node->next->previous = node->previous;
                                node->previous->next = node->next;
                                UpdateMiddleReduceLeft();
                                free(node);
                            }

                            else if (start == middle) {
                                UpdateMiddleReduce();
                                node->next->previous = node->previous;
                                node->previous->next = node->next;
                                free(node);
                            }

                            else if (middle < start && start < last) {
                                node->next->previous = node->previous;
                                node->previous->next = node->next;
                                UpdateMiddleReduceRight();
                                free(node);
                            }

                            else if (start == last) {
                                tail = node->previous;
                                UpdateMiddleReduceRight();
                                free(node);
                            }

                            // remove node in List
                            
                            range--;

                            count--;

                            start++;
                        }
                    }

                    return *copy;

                }
                // splice (index)start, (count)delete, (data)put
                // map
                // flat
                // filter
                // forEach
                // forEachRev
            
            // public
        };

        template<typename T>
        class Dict {

            private:
                struct Item {

                    std::string key;
                    T value;
                };

            public:

                void SetItem(std::string key, T value) {}
                void GetItem(std::string key) {}

            // public
        };

        // NodeList

    };

    // Tuple
    // Dict
    // NodeList

}

#endif
#endif
