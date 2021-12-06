#pragma once
#ifndef ORION_ARRAY_H
#define ORION_ARRAY_H

#include"dtype.h"
#include"debug.h"

#define Type Se::Abstract::Type
#define ReturnType Se::Abstract::ReturnType

#ifdef __cplusplus
extern "C++" {
    
    namespace Se {

        template<typename T>
        class List {

            private:

                struct Node {

                    struct Node* next;

                    T data;

                    Node(void) {

                        next = nullptr;
                    }
                    ~Node() {}

                };

                Node* head;
                Node* tail;

                u64 dataCount;

                Node& search(const u64& index) {

                    Node* node;

                    node = head;

                    for (u64 i = 0; i < dataCount; i++) {

                        if (index == i) break;
                        node = node->next;
                    }

                    return *node;
                }

                List& _concat(void) {

                    return *(new List());
                }

                template<typename... Args>
                friend List& _concat(List& array, Args&&... arguments);

                template<typename... Args>
                List& _concat(List& array, Args&&... arguments) {

                    List* copy;
                    List* temp;
                    Node* node;

                    copy = &(array.copy());
                    temp = &_concat(arguments...);

                    if (!(temp->dataCount > 0)) return *copy;
                    node = temp->head;

                    while (node != nullptr) {

                        copy->push(node->data);
                        node = node->next;
                    }

                    return *copy;
                }

                void put(const u64& index, const T& value) {

                    Node* curr;
                    Node* node;
                    Node* prev;

                    node = new Node();
                    prev = nullptr;

                    curr = head;
                    for (u64 _ = 0; _ < index; _++) {

                        if (curr->next == nullptr) break;

                        prev = curr;
                        curr = curr->next;
                    }

                    node->data = value;
                    node->next = curr;

                    if (prev != nullptr) prev->next = node;
                    else head = node;

                    dataCount++;
                }

                void puts_ptr(Node*) {

                    return;

                }

                template<typename... Args>
                void puts_ptr(Node* curr, T value, Args&&... arguments) {

                    Node* node;
                    Node* swap;

                    node = new Node;
                    node->data = value;
                    swap = nullptr;

                    dataCount++;

                    if (tail == curr) tail = node;

                    if (curr != nullptr) {

                        swap = curr->next;
                        curr->next = node;
                        node->next = swap;

                        puts_ptr(node, arguments...);
                        return;
                    }

                    swap = head;
                    head = node;
                    node->next = swap;
                    
                    puts_ptr(node, arguments...);

                    return;
                }
            
            // private

            public:

                List(void) {

                    head = nullptr;
                    tail = nullptr;
                    
                    dataCount = 0;
                }

                // List(List& other) { // conflict by copy-function
                //     List();
                //     Node* node;
                //     node = other.head;
                //     while (node != nullptr) {
                //         this->push(node->data);
                //         node = node->next;
                //     }
                // }
                
                ~List() {}

                // auto& firstNode(void) {
                //     if (head == nullptr) return *(new Node);
                //     return *head;
                // }

                // auto& lastNode(void) {
                //     if (tail == nullptr) return *(new Node);
                //     return *tail;
                // }

                void push(const T& value) {

                    Node* node;

                    node = new Node();

                    node->data = value;


                    if (head == nullptr) {

                        head = node;
                        tail = head;

                    } else {

                        tail->next = node;
                        tail = node;
                    }

                    dataCount++;
                }

                auto getitem(const u64& index) {

                    Node* node;
                    ReturnType<T> rty;

                    rty.type = Type::FAIL;

                    if (index < dataCount) {

                        node = &search(index);

                        rty.type = Type::SUCCESS;
                        rty.data = node->data;
                    }

                    return rty;
                }

                void setitem(const u64& index, const T& value) {

                    Node* node;

                    if (index < dataCount) {

                        node = &search(index);
                        node->data = value;
                    }
                }

                u64 size(void) {

                    return dataCount;
                }

                void remove(const u64& index) {

                    Node* node;
                    Node* prev;

                    if (!(index < dataCount)) return;

                    node = head;
                    prev = nullptr;

                    for (u64 _ = 0; _ < index; _++) {
                        
                        if (node->next == nullptr) break;

                        prev = node;
                        node = node->next;
                    }

                    if (head == node) {

                        if (tail == node) tail = node->next;
                        head = node->next;

                    } else if (tail == node) {

                        if (prev != nullptr) prev->next = nullptr;
                        tail = prev;
                        
                    
                    } else {

                        if (prev != nullptr) prev->next = node->next;
                    }

                    
                    free(node);

                    dataCount--;
                }

                List& copy(void) {

                    List* temp;
                    Node* node;

                    node = head;
                    temp = new List();

                    // while (node != nullptr) {

                    //     temp->push(node->data);
                    //     node = node->next;
                    // }

                    for (u64 _ = 0; _ < dataCount; _++) {

                        temp->push(node->data);
                        node = node->next;
                    }

                    return *temp;
                }

                template<typename... Args>
                List& concat(Args&&... arguments) {

                    return _concat(*this, arguments...);
                }

                auto& first(void) {

                    if (head != nullptr) return *head;
                    return *(new Node());
                }

                auto& top(void) {

                    if (tail != nullptr) return *tail;
                    return *(new Node());
                }

                T& shift(void) {

                    Node* node;
                    T data;

                    node = head;
                    data = node->data;
                    head = node->next;
                    dataCount--;
                    
                    free(node);
                    
                    T& refdata = *(new T);
                    refdata = data;

                    return refdata;
                }
                
                T& pop(void) {

                    Node* node;
                    Node* prev;
                    T data;
                    
                    node = tail;
                    prev = head;
                    data = node->data;
                    
                    while (prev->next != node) {
                    
                        prev = prev->next;
                    
                    }

                    tail = prev;
                    tail->next = nullptr;
                    dataCount--;
                    
                    free(node);

                    T& refdata = *(new T);
                    refdata = data;

                    return refdata;
                }

                auto indexOf(const T& value) {

                    Node* node;
                    ReturnType<u64> rty;
                    // u64 i;

                    node = head;
                    rty.type = Type::FAIL;
                    // i = 0;

                    // while (node != nullptr) {

                    //     if (node->data == value) {

                    //         rty.type = Type::SUCCESS;
                    //         rty.data = i;
                    //         break;
                    //     }

                    //     node = node->next;
                    //     i++;
                    // }

                    for (u64 i = 0; i < dataCount; i++) {

                        if (node->data == value) {

                            rty.type = Type::SUCCESS;
                            rty.data = i;
                            break;
                        }

                        node = node->next;
                    }

                    return rty;
                }

                List& reverse(void) {

                    Node* node;
                    Node* prev;
                    Node* swap;

                    node = head;

                    prev = nullptr;
                    swap = nullptr;

                    // while (node != nullptr) {

                    //     prev = node;
                    //     node = node->next;
                    //     prev->next = swap; 
                    //     swap = prev;

                    // }

                    for (u64 i = 0; i < dataCount; i++) {

                        prev = node;
                        node = node->next;
                        prev->next = swap; 
                        swap = prev;

                    }

                    swap = head;
                    head = tail;
                    tail = swap;

                    return *this;
                }

                bool includes(const T& value) {

                    Node* node;

                    node = head;
                    
                    // while (node != nullptr) {

                    //     if (node->data == value) return true;

                    //     node = node->next;
                    // }

                    for (u64 _ = 0; _ < dataCount; _++) {

                        if (node->data == value) return true;

                        node = node->next;

                    }

                    return false;
                }

                List& slice(u64 start, u64 end) {

                    List* temp;
                    Node* node;

                    temp = new List();
                    node = nullptr;

                    if (dataCount < end) end = dataCount;

                    if (start < end) {

                        end = end - start;

                        node = &search(start);

                        while(!!end) {

                            temp->push(node->data);
                            node = node->next;
                            end--;
                        }
                    }

                    return *temp;
                }

                void puts(u64) {

                }

                template<typename... Args>
                void puts(const u64& index, T value, Args&&... arguments) {

                    if (dataCount < index) return;
                    else if (dataCount == index) push(value);
                    else put(index, value);

                    puts(index + 1, arguments...);
                }

                template<typename... Args>
                List& splice(u64 start, u64 deleteCount, Args&&... arguments) {

                    List* copy;

                    Node* node;
                    Node* swap;
                    Node* prev;

                    copy = new List();

                    node = nullptr;
                    swap = nullptr;
                    prev = nullptr;

                    if (dataCount < (start + deleteCount)) deleteCount = dataCount - start;

                    // search 
                    node = head;
                    for (u64 _ = 0; _ < start; _++) {

                        if (node->next == nullptr) break;

                        prev = node;
                        node = node->next;
                    }

                    swap = node;

                    // delete 
                    dataCount = dataCount - deleteCount;
                    for (u64 _ = 0; _ < deleteCount; _++) {

                        node = swap;
                        swap = node->next;

                        if (head == node) {

                            if (tail == node) tail = node->next;
                            head = node->next;

                        } else if (tail == node) {

                            if (prev != nullptr) prev->next = nullptr;
                            tail = prev;
                            
                        
                        } else {

                            if (prev != nullptr) prev->next = node->next;
                        }

                        free(node);
                    }

                    //

                    // node = swap;
                    // prev

                    // puts(start, arguments...);
                    puts_ptr(prev, arguments...);
                    return *copy;
                }

                T& operator[](const u64& index) {

                    if (!(index < dataCount)) return (new Node())->data;

                    Node* node;

                    node = &search(index);

                    return node->data;
                }

                template<typename _Cast>
                void display(void) {

                    Node* node;

                    node = head;

                    std::cout << "[ ";

                    if (dataCount > 0) {

                        while (node->next != nullptr) {

                            std::cout << (_Cast)(node->data) << ", ";
                            node = node->next;
                        }

                        std::cout << (_Cast)(node->data) << " ]" << std::endl;
                    
                    } else {

                        std::cout << " ]" << std::endl;
                    }

                }

                void destroy(void) {

                    Node* node;
                    Node* swap;

                    node = head;
                    swap = nullptr;

                    // while(node != nullptr) {

                    //     temp = node->next;
                    //     free(node);
                    //     node = temp;
                    // }

                    swap = node;

                    for (u64 _ = 0; _ < dataCount; _++) {

                        node = swap;
                        swap = node->next;
                        free(node);
                    }

                    dataCount = 0;

                    delete this;
                }

            // public
        };
    };

    //TODOs
    /*
        put
        puts_ptr
        remove
        copy
        shift
        pop
        indexOf
        reverse
        includes
        slice
        splice
        destroy
    */

    namespace Ex {

        template<typename T>
        class List {

            private:

                struct Node {

                    struct Node* previous;
                    struct Node* next;

                    T data;

                    Node(void) {

                        previous = nullptr;
                        next = nullptr;
                    }
                    ~Node() {}

                };

                struct NodeIterator {

                    Node* begin;
                    Node* end;

                    NodeIterator(void) {

                        begin = nullptr;
                        end = nullptr;
                        
                    }
                    ~NodeIterator() {}
                };

                Node* head;
                Node* midz;
                Node* tail;

                u64 dataCount;

                u64 getMiddlePos(void) {

                    return ((dataCount & 1) == 1 ? (dataCount + 1) / 2 : dataCount / 2) - 1;
                }

                u64 getMiddlePos(u64 m_size) {

                    return ((m_size & 1) == 1 ? (m_size + 1) / 2 : m_size / 2) - 1;
                }

                Node& middleSearchChild(const u64& index, u64 m_size, NodeIterator nodeIterator) {

                    Node* node;
                    u64 middle, i;

                    middle = getMiddlePos(m_size);
                    i = 0;

                    if (index <= middle) {

                        node = nodeIterator.begin;

                        while (i <= middle) {

                            if (index == i) break;

                            node = node->next;
                            i++;
                        }
                    } else if (middle < index) {

                        node = nodeIterator.end;
                        i = m_size - 1;

                        while (middle < i) {

                            if (index == i) break;

                            node = node->previous;
                            i--;
                        }
                    }


                    if (node == nullptr) node = new Node();

                    return *node;
                }

                Node& middleSearch(const u64& index) {

                    Node* node;
                    NodeIterator nodeIterator;
                    u64 middle, m_size;

                    node = new Node();
                    nodeIterator.begin = head;
                    middle = getMiddlePos();
                    m_size = 0;

                    if (index <= middle) {

                        if (!!(dataCount & 1)) {

                            m_size = middle;

                            if (index < middle) nodeIterator.end = midz->previous;

                            if (middle == index) return *midz; 

                        } else {

                            m_size = middle + 1;
                            nodeIterator.end = midz;
                        }

                        // LOG("using middleSearch, index at: " << index << " Left")
                        node = &middleSearchChild(index, m_size, nodeIterator);

                    } else {

                        nodeIterator.begin = midz->next;
                        nodeIterator.end = tail;

                        // LOG("using middleSearch, index at: " << index << " Right")
                        node = &middleSearchChild(index - middle - 1, m_size, nodeIterator);
                    }

                    return *node;
                }

                void updateMiddleReduce(void) {

                    u64 vmiddle, middle;

                    vmiddle = getMiddlePos(dataCount - 1);
                    middle = getMiddlePos();

                    if (middle == vmiddle) {

                        midz = midz->next;

                    } else if (vmiddle < middle) {

                        midz = midz->previous;

                    }
                }

                void updateMiddleLeftReduce(void) {

                    u64 vmiddle, middle;

                    vmiddle = getMiddlePos(dataCount - 1);
                    middle = getMiddlePos();

                    if (middle == vmiddle) {

                        midz = midz->next;

                    }
                }

                void updateMiddleRightReduce(void) {

                    u64 vmiddle, middle;

                    vmiddle = getMiddlePos(dataCount - 1);
                    middle = getMiddlePos();

                    if (vmiddle < middle) {

                        midz = midz->previous;

                    }
                }

                void updateMiddleLeftAccrue(void) {

                    u64 vmiddle, middle;

                    vmiddle = getMiddlePos(dataCount + 1);
                    middle = getMiddlePos();

                    if (middle == vmiddle) {

                        midz = midz->previous;
                    }
                }

                void updateMiddleAccrue(void) {

                    updateMiddleLeftAccrue();
                }

                void updateMiddleRightAccrue(void) {

                    u64 vmiddle, middle;

                    vmiddle = getMiddlePos(dataCount + 1);
                    middle = getMiddlePos();

                    if (middle < vmiddle) {

                        midz = midz->next;

                    }
                }

                List& _concat(void) {

                    return *(new List());
                }

                template<typename... Args>
                friend List& _concat(List& array, Args&&... arguments);

                template<typename... Args>
                List& _concat(List& array, Args&&... arguments) {

                    List* copy;
                    List* temp;
                    Node* node;

                    copy = &(array.copy());
                    temp = &_concat(arguments...);

                    if (!(temp->dataCount > 0)) return *copy;
                    node = temp->head;

                    while (node != nullptr) {

                        copy->push(node->data);
                        node = node->next;
                    }

                    return *copy;
                }

                void put(const u64& index, const T& value) {

                    Node* node;
                    Node* temp;

                    u64 middle;

                    node = &middleSearch(index);
                    temp = new Node();

                    middle = getMiddlePos();

                    temp->data = value;

                    temp->next = node;
                    temp->previous = node->previous;

                    if (node->previous != nullptr) node->previous->next = temp;
                    else head = temp;

                    node->previous = temp;

                    if (index < middle) updateMiddleLeftAccrue();
                    else if (middle == index) updateMiddleAccrue();
                    else updateMiddleRightAccrue();

                    dataCount++;

                }

            // private

            public:

                List(void) {

                    head = nullptr;
                    midz = nullptr;
                    tail = nullptr;

                    dataCount = 0;

                }

                // List(List& other) { // conflict by copy-function
                //     List();
                //     Node* node;
                //     node = other.head;
                //     while (node != nullptr) {
                //         this->push(node->data);
                //         node = node->next;
                //     }
                // }

                List(Se::List<T>& other) {

                    List();

                    for(u64 i = 0; i < other.size(); i++) {
                        
                        this->push(other.getitem(i));
                    }
                }
                
                ~List() {}

                // auto& firstNode(void) {
                //     if (head == nullptr) return *(new Node);
                //     return *head;
                // }

                // auto& lastNode(void) {
                //     if (tail == nullptr) return *(new Node);
                //     return *tail;
                // }

                void push(const T& value) {

                    Node* node;

                    node = new Node();
                    node->data = value;

                    if (head == nullptr) {

                        head = node;
                        midz = head;
                        tail = midz;
                    
                    } else {

                        tail->next = node;
                        node->previous = tail;
                        tail = node;

                        if (!(dataCount & 1)) {

                            midz = midz->next;
                        }
                    }

                    dataCount++;
                }

                auto getitem(const u64& index) {

                    Node* node;
                    ReturnType<T> rty;

                    rty.type = Type::FAIL;

                    if (index < dataCount) {

                        node = &middleSearch(index);

                        rty.type = Type::SUCCESS;
                        rty.data = node->data;
                    }

                    return rty;
                }

                void setitem(const u64& index, const T& value) {

                    Node* node;

                    if (index < dataCount) {

                        node = &middleSearch(index);
                        node->data = value;
                    }
                }

                u64 size(void) {

                    return dataCount;
                }

                void remove(const u64& index) {


                    Node* node;
                    u64 middle;

                    if (!(index < dataCount)) return;

                    node = &middleSearch(index);
                    middle = getMiddlePos();
                    
                    if (node != tail) {
                        if (node->next != nullptr) node->next->previous = node->previous;
                    } else {
                        tail = node->previous;
                        if (tail != nullptr) tail->next = nullptr;
                    }
                    
                    if (node != head) {
                        if (node->previous != nullptr) node->previous->next = node->next;
                    } else {
                        head = node->next;
                        if (head != nullptr) head->previous = nullptr;
                    }

                    if (index < middle) updateMiddleLeftReduce();
                    else if (middle == index) updateMiddleReduce();
                    else updateMiddleRightReduce();

                    free(node);

                    dataCount--;
                }

                List& copy(void) {

                    List* m_copy;
                    Node* node;

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

                    return _concat(*this, arguments...);
                }

                auto& first(void) {

                    if (head != nullptr) return *head;
                    return *(new Node());
                }

                auto& top(void) {

                    if (tail != nullptr) return *tail;
                    return *(new Node());
                }

                T shift(void) {

                    T value;
                    Node* node;

                    node = head;
                    value = node->data;
                    head = node->next;
                    head->previous = nullptr;

                    updateMiddleLeftReduce();

                    free(node);
                    dataCount--;

                    return value;
                }
                
                T pop(void) {

                    T value;
                    Node* node;

                    node = tail;
                    value = node->data;
                    tail = node->previous;
                    tail->next = nullptr;

                    updateMiddleRightReduce();

                    free(node);
                    dataCount--;

                    return value;
                }

                auto indexOf(const T& value) {

                    Node* node;
                    ReturnType<u64> rty;

                    u64 i;

                    node = head;
                    rty.type = Type::FAIL;
                    i = 0;

                    while (node != nullptr) {

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

                    Node* node;
                    Node* temp;
                    Node* swap;

                    node = head;

                    temp = nullptr;
                    swap = nullptr;

                    while (node != nullptr) {

                        temp = node->next;

                        swap = temp;
                        node->next = node->previous;
                        node->previous = swap;

                        node = temp;

                    }

                    if (dataCount > 3) {
                        if (!(dataCount & 1)) midz = midz->previous;
                    } else if (dataCount == 2) midz = tail;

                    swap = head;
                    head = tail;
                    tail = swap;

                    return *this;
                }

                bool includes(const T& value) {

                    Node* node;

                    node = head;

                    while (node != nullptr) {

                        if (node->data == value) return true;

                        node = node->next;
                    }

                    return false;
                }

                List& slice(u64 start, u64 end) {

                    List* copy;
                    Node* node;

                    copy = new List();
                    node = nullptr;

                    if (dataCount < end) end = dataCount;

                    if (start < end) {

                        end = end - start;

                        node = &middleSearch(start);

                        while (!!end) {

                            copy->push(node->data);
                            node = node->next;
                            end--;
                        }
                    }

                    return *copy;
                }

                void puts(u64) {

                }

                template<typename... Args>
                void puts(const u64& index, T value, Args&&... arguments) {

                    if (dataCount < index) return;
                    else if (dataCount == index) push(value);
                    else put(index, value);

                    puts(index + 1, arguments...);
                }

                template<typename... Args>
                List& splice(u64 start, u64 deleteCount, Args&&... arguments) {

                    List* copy;

                    Node* node;
                    Node* temp;
                    
                    u64 middle;
                    
                    copy = new List();

                    node = nullptr;
                    temp = nullptr;
                    
                    middle = 0;

                    if (dataCount < (start + deleteCount)) deleteCount = dataCount - start;

                    temp = &middleSearch(start);

                    while (!!deleteCount) {

                        node = temp;
                        temp = node->next;

                        middle = getMiddlePos();
                        
                        if (node != tail) node->next->previous = node->previous;
                        else tail = node->previous;
                        
                        if (node != head) node->previous->next = node->next;
                        else head = node->next;

                        if (start < middle) updateMiddleLeftReduce();
                        else if (middle == start) updateMiddleReduce();
                        else updateMiddleRightReduce();

                        copy->push(node->data);

                        free(node);

                        deleteCount--;
                        dataCount--;
                    }

                    puts(start, arguments...);
                    return *copy;
                }

                T& operator[](const u64& index) {

                    if (!(index < dataCount)) return (new Node())->data;

                    Node* node;

                    node = &middleSearch(index);

                    return node->data;
                }

                template<typename _Cast>
                void display(void) {

                    Node* node;

                    node = head;

                    std::cout << "[ ";

                    if (dataCount > 0) {

                        while (node->next != nullptr) {

                            std::cout << (_Cast)(node->data) << ", ";
                            node = node->next;
                        }

                        std::cout << (_Cast)(node->data) << " ]" << std::endl;
                    
                    } else {

                        std::cout << " ]" << std::endl;
                    }

                }

                void destroy(void) {

                    Node* node;
                    Node* temp;

                    node = head;
                    temp = nullptr;

                    while(node != nullptr) {

                        temp = node->next;
                        free(node);
                        node = temp;
                    }

                    dataCount = 0;

                    delete this;
                }

            // public
        };
    };

}

#endif

#endif
