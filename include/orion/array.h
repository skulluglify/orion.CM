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

                ui64 GetMiddlePos(ui64 m_size) {
                    return (m_size & 1) == 1 ? (m_size + 1) / 2 : m_size / 2;
                }

                Node* MiddleSearchChild(ui64 m_size, ui64 index, NodeIterator nodeIterator) {

                    Node* node;
                    // Node* begin;
                    // Node* end;
                    ui64 middle, i;
                    // node = new Node();
                    // begin = new Node();
                    // end = new Node();
                    // begin = nodeIterator.begin;
                    // end = nodeIterator.end;
                    middle = GetMiddlePos(m_size) - 1;
                    
                    if (index <= middle) {  // ODD | EVEN AS SAME MEAN
                        // node = begin;
                        node = nodeIterator.begin;
                        i = 0;
                        while (i <= middle) {
                            if (index == i) break;
                            node = node->next;
                            i++;
                        }
                    } else if (middle < index) { // ODD | EVEN AS SAME
                        // node = end;
                        node = nodeIterator.end;
                        i = m_size - 1;
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
                    ui64 middle;
                    ui64 m_size;

                    node = new Node();
                    middle = GetMiddlePos(count) - 1;
                    m_size = 0;
                    nodeIterator.begin = head; // start | middle as same
                    
                    if (index <= middle) {
                        if ((count & 1) == 1) { // ODD
                            m_size = middle;
                            if (index < middle) {
                                nodeIterator.end = midz->previous;
                            }
                            if (index == middle) return midz;
                        } else { // EVEN
                            m_size = middle + 1;
                            nodeIterator.end = midz;
                        }
                        node = MiddleSearchChild(m_size, index, nodeIterator);
                    } else if (middle < index) { // ODD | EVEN AS SAME
                        nodeIterator.begin = midz->next;
                        nodeIterator.end = tail;
                        node = MiddleSearchChild(m_size, index - middle - 1, nodeIterator);
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
                    else if (vmiddle < middle) {
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

                void UpdateMiddleReduceRight() { // if right loss

                    ui64 vmiddle = GetMiddlePos(count - 1) - 1; // virtual
                    ui64 middle = GetMiddlePos(count) - 1;

                    if (vmiddle < middle) {
                        midz = midz->previous;
                    }
                }

                // ********************** FOR REMOVE FUN ********************** //
                // ********************** FOR  PUT   FUN ********************** //

                void UpdateMiddleAccrue() {

                    UpdateMiddleAccrueLeft();
                }

                void UpdateMiddleAccrueLeft() {

                    ui64 vmiddle = GetMiddlePos(count + 1) - 1; // virtual
                    ui64 middle = GetMiddlePos(count) - 1;

                    if (vmiddle == middle) {
                        midz = midz->previous;
                    }
                }

                void UpdateMiddleAccrueRight() {

                    ui64 vmiddle = GetMiddlePos(count + 1) - 1; // virtual
                    ui64 middle = GetMiddlePos(count) - 1;

                    if (middle < vmiddle) {
                        midz = midz->next;
                    }
                }

                // ********************** FOR  PUT   FUN ********************** //

                void OmitPtr(Node* node) {

                    if (node != tail) node->next->previous = node->previous;
                    if (node != head) node->previous->next = node->next;
                    // free(node);

                };

                void RemovePtr(Node* node, ui64 index) {

                    ui64 middle;
                    ui64 last;


                    middle = GetMiddlePos(count) -1;
                    last = count > 0 ? count -1 : 0;

                    if (node == nullptr) return;

                    if (index < count) {

                        if (index < middle) {

                            if (index != 0) OmitPtr(node);
                            else head = node->next;

                            UpdateMiddleReduceLeft();
                        }

                        else if (index == middle) {

                            OmitPtr(node);

                            UpdateMiddleReduce();
                        }

                        else if (middle < index) {

                            if (index != last) OmitPtr(node);
                            else tail = node->previous;

                            UpdateMiddleReduceRight();
                        }

                        free(node);
                    }

                    count--;
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
                    node = &arraySafe->First();

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
                    returnType.type = returnType.FAIL;
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
                            // return returnType;
                        };
                    }

                    
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
                    // ui64 last;

                    // node = nullptr;
                    // last = count -1;

                    // node = head;
                    
                    if (index < count) {

                        // while (index > 0) {
                            // node = node->next;
                            // index--;
                        // }

                        node = MiddleSearch(index); // 4 virtual abstract


                        // ui64 middle = GetMiddlePos(count) - 1;
                        
                        // // LOG("middle " << middle)

                        // // head as same Shift
                        // // ======================================================
                        // if (index == 0) {

                        //     if (head->next != nullptr) {
                        //         head = head->next;
                        //         UpdateMiddleReduceLeft();
                        //         free(head->previous);
                        //     }

                        // }
                        // // ======================================================

                        // // middle
                        // // ======================================================
                        // else if (index == middle) {    

                        //     Node* displace;
                        //     displace = midz;
                        //     if (displace->previous != nullptr && displace->next != nullptr) {
                        //         UpdateMiddleReduce();
                        //         displace->next->previous = displace->previous;
                        //         displace->previous->next = displace->next;
                        //         free(displace);
                        //     }
                        // }
                        // // ======================================================

                        // // tail as same Pop
                        // // ======================================================
                        // else if (index == last) {

                        //     if (tail->previous != nullptr) {
                        //         tail = tail->previous;
                        //         UpdateMiddleReduceRight();
                        //         free(tail->next);
                        //     }
                        // }
                        // // ======================================================

                        // else {

                        //     // random node
                        //     // update midz if left or right
                        //     if (index < middle) {

                        //         node->previous->next = node->next;
                        //         node->next->previous = node->previous;
                        //         UpdateMiddleReduceLeft();
                        //         free(node);

                        //     }
                        //     else if (middle < index) {

                        //         node->previous->next = node->next;
                        //         node->next->previous = node->previous;
                        //         UpdateMiddleReduceRight();
                        //         free(node);

                        //     }
                        // }


                        RemovePtr(node, index);

                        // count--;
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

                //     node = &B->First();
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

                Node& First() {

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
                    Node* copy;
                    Node* prev;
                    Node* swap;

                    copy = head;
                    safe = nullptr;
                    node = nullptr;
                    prev = nullptr;
                    swap = nullptr;

                    if (count > 3) {
                        while (true) {

                            prev = copy;
                            if (prev == nullptr) break;
                            
                            node = prev->next;
                            if (node == nullptr) break;
                            
                            // LOG("check at: " << (int)prev->data)

                            safe = node->next;
                            copy = safe;

                            node->next = prev;
                            node->previous = safe;
                            
                            swap = prev->next;
                            prev->next = prev->previous;
                            prev->previous = swap;
                        }
                    }

                    if (count > 3) {
                        if ((count & 1) == 0) midz = midz->previous;
                    } else if (count == 2) midz = tail;

                    swap = head;
                    head = tail;
                    tail = swap;

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

                    // ui64 middle;
                    // ui64 range;
                    // ui64 length;
                    // ui64 last;
                    
                    copy = new List();
                    safe = nullptr;
                    node = nullptr;

                    // middle = GetMiddlePos(count) - 1;
                    // range = 0;
                    // length = 0;
                    // last = count > 0 ? count - 1 : 0;

                    // if (start < 0) start = 0;
                    if (count < end) end = count;

                    if (start < end) {

                        // length = end - start + 1;
                        end = end - start;
                        // length = range;

                        // while (start != 0) {

                        //     node = node->next;
                            
                        //     start--;
                        // }

                        safe = MiddleSearch(start);

                        while (end != 0) {

                            node = safe;

                            copy->Push(node->data);
                            
                            safe = node->next;

                            // remove node in List
                            // if (start == 0) {
                            //     head = node->next;
                            //     UpdateMiddleReduceLeft();
                            //     free(node);
                            // }

                            // else if (0 < start && start < middle) {
                            //     node->next->previous = node->previous;
                            //     node->previous->next = node->next;
                            //     UpdateMiddleReduceLeft();
                            //     free(node);
                            // }

                            // else if (start == middle) {
                            //     UpdateMiddleReduce();
                            //     node->next->previous = node->previous;
                            //     node->previous->next = node->next;
                            //     free(node);
                            // }

                            // else if (middle < start && start < last) {
                            //     node->next->previous = node->previous;
                            //     node->previous->next = node->next;
                            //     UpdateMiddleReduceRight();
                            //     free(node);
                            // }

                            // else if (start == last) {
                            //     tail = node->previous;
                            //     UpdateMiddleReduceRight();
                            //     free(node);
                            // }

                            // remove node in List

                            RemovePtr(node, start);

                            // LOG("DEBUG: " << start << " at: " << (int)(node->data) << " m_size: " << count << " middle at: " << (int)midz->data)
                            
                            // count++;
                            
                            end--;

                            // count--;

                            // start++;
                        }

                        // Node* test;
                        // test = head;
                        // while (test != nullptr) {

                        //     LOG("data: " << (int)(test->data))

                        //     test = test->next;
                        // }

                        // count = count - length;
                    }

                    return *copy;

                }

                void Put(ui64 index, T data) {

                    Node* node;
                    Node* safe;

                    ui64 middle;
                    // ui64 last;

                    safe = MiddleSearch(index);

                    node = new Node();

                    middle = GetMiddlePos(count) -1;

                    // last = count -1;


                    node->data = data;

                    if (index < middle) {

                        if (index == 0) head = node;

                        node->next = safe;
                        node->previous = safe->previous;
                        if (safe->previous != nullptr && index > 0) safe->previous->next = node;
                        else head = node;
                        safe->previous = node;

                        UpdateMiddleAccrueLeft();
                    }
                    else if (index == middle) {

                        node->next = safe;
                        node->previous = safe->previous;
                        if (safe->previous != nullptr && index > 0) safe->previous->next = node;
                        else head = node;
                        safe->previous = node;
                        UpdateMiddleAccrue();

                    }
                    else if (middle < index) {

                        // if (index == last) {}
                        node->next = safe;
                        node->previous = safe->previous;
                        if (safe->previous != nullptr && index > 0) safe->previous->next = node;
                        else head = node;
                        safe->previous = node;
                        UpdateMiddleAccrueRight(); 
                    }

                    count++;

                }

                void Puts(ui64) {

                    // return;
                }

                template<typename... Args>
                void Puts(ui64 index, T data, Args&&... arguments) {

                    if (count == index) Push(data);
                    else Put(index, data);

                    // LOG("index at: " << index)

                    Puts(index + 1, arguments...);
                }

                // splice (index)start, (count)delete, (data)put
                template<typename... Args>
                List& Splice(ui64 start, ui64 deleteCount, Args&&... arguments) {

                    List* copy;
                    // copy = new List();
                    copy = &Slice(start, start + deleteCount);

                    // LOG("deleteCount: " << deleteCount)

                    Puts(start, arguments...);
                    return *copy;
                }
                
                // map
                // flat
                // filter
                // forEach
                // forEachRev
                // sort, bubble sort

                T& operator[](int index) {

                    Node* node;
                    node = MiddleSearch(index);
                    return node->data;
                }
            
            // public
        };

        // Dict List
        // List
        // Get Set Remove

        // ComplexList
        // List


        template<typename T>
        class Dict {

            private:

                struct Item {

                    std::string key;
                    T value;
                };

                List<Item>* data;

                struct ItemSet {

                    private:
                    
                        Item* m_item;
                        Dict<T>* m_dict;

                    public:

                        ItemSet(Dict<T>* dict, Item& item) {

                            m_item = &item;
                            m_dict = dict;

                        }

                        ~ItemSet() {}

                        T& valueOf() {

                            return m_item->value;
                        }

                        void operator= (T value) {


                            // LOG("test value: " << (int)value)

                            m_item->value = value;

                            // auto detect if not pushing
                            m_dict->SetItem(m_item->key, m_item->value);
                        }

                    // public
                };

            public:

                Dict() {

                    data = new List<Item>();
                }

                ~Dict() {}

                bool Contains(std::string key) {

                    auto *node = &data->First();
                    while (node != nullptr) {

                        if (node->data.key == key) return true;

                        node = node->next;
                    }

                    return false;
                }

                void SetItem(std::string key, T value) {

                    auto *node = &data->First();
                    while (node != nullptr) {

                        if (node->data.key == key) {

                            node->data.value = value;

                            return;
                        }

                        node = node->next;
                    }

                    Item* item;
                    item = new Item();
                    item->key = key;
                    item->value = value;
                    data->Push(*item);

                    // if (!Contains(key)) {
                    
                    //     Item* item;
                    //     item = new Item();
                    //     item->key = key;
                    //     item->value = value;
                    //     data->Push(*item);
                    
                    // } else {

                    // }
                }

                ReturnType<T> GetItem(std::string key) {

                    // MiddleSearch Unused

                    ReturnType<T> returnType;
                    returnType.type = returnType.FAIL;

                    auto *node = &data->First();
                    while (node != nullptr) {

                        if (node->data.key == key) {

                            returnType.type = returnType.OK;
                            returnType.value = node->data.value;
                            break;
                        }

                        node = node->next;
                    }

                    return returnType;
                }

                template<typename... Args>
                void Update(Dict& dict, Args&&... arguments) {

                    // dict, update, merge, replace

                    Update(arguments...);
                }

                ItemSet& operator[](std::string key) {


                    auto *node = &data->First();
                    while (node != nullptr) {

                        if (node->data.key == key) {

                            ItemSet *itemSet;
                            itemSet = new ItemSet(this, node->data);

                            return *itemSet;
                            // break;
                        }

                        node = node->next;
                    }

                    // missing data
                    
                    Item item;
                    item.key = key;

                    ItemSet *itemSet;
                    itemSet = new ItemSet(this, item);
                    return *itemSet;
                    
                }

                // Keys
                // Items

            // public
        };

        // NodeList

    };

    // Tuple
    // NodeList

}

#endif
#endif
