#pragma once
#ifndef ORION_ARRAY_H
#define ORION_ARRAY_H

#include"dtype.h"
#include"debug.h"

#define Type se::abs::Type
#define ReturnType se::abs::ReturnType

#ifdef __cplusplus
extern "C++" {
    
    namespace Se {

        template<typename T>
        class List {

            private:

                struct Node {

                    struct Node *next;

                    T data;

                    Node(void) {}
                    ~Node() {}

                };

                Node *head;
                Node *tail;

                u64 dataCount;

                Node& search(u64 index) {

                    Node *node;
                    u64 i;

                    node = head;
                    i = 0;

                    while (!(index == i)) {

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
                    List *temp;
                    Node *node;

                    copy = &(array.copy());
                    temp = &_concat(arguments...);

                    if (!(temp->dataCount > 0)) return *copy;
                    node = &(temp->first());

                    while (node != nullptr) {

                        copy->push(node->data);
                        node = node->next;
                    }

                    return *copy;
                }

                void put(u64 index, T value) {

                    Node *node;
                    Node *temp;
                    Node *prev;

                    node = &search(index);
                    temp = new Node();
                    prev = get_previous_ptr(node);

                    temp->data = value;

                    temp->next = node;

                    if (prev->next != nullptr) prev->next = temp;
                    else head = temp;

                    dataCount++;
                }

                Node *get_previous_ptr(Node *node) {

                    Node* prev;
                    prev = head;

                    if (prev != node) {

                        while (prev->next != node) {

                            prev = prev->next;
                        }

                    } else {

                        prev = nullptr;
                    }

                    return prev;
                }
            
            // private

            public:

                List(void) {

                    head = nullptr;
                    tail = nullptr;
                    dataCount = 0;
                }
                
                ~List() {}

                void push(T value) {

                    Node *node;

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

                        node = &search(index);
                        node->data = value;
                    }
                }

                u64 size(void) {

                    return dataCount;
                }

                void remove(u64 index) {

                    Node *node;
                    Node *prev;

                    if (!(index < dataCount)) return;

                    node = &search(index);
                    prev = get_previous_ptr(node);

                    if (head == node) head = node->next;
                    if (tail == node) {
                        tail = prev;
                        if (tail != nullptr) tail->next = nullptr;
                    } else {
                        if (prev != nullptr) prev->next = node->next;
                    }

                    
                    free(node);

                    dataCount--;
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

                    Node *node;
                    T data;
                    node = head;
                    data = node->data;
                    head = node->next;
                    free(node);
                    dataCount--;
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
                    dataCount--;
                    return data;
                }

                auto indexOf(T value) {

                    Node *node;
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

                    Node *node;
                    Node *temp;
                    Node *swap;

                    node = head;

                    temp = nullptr;
                    swap = nullptr;

                    while (node != nullptr) {

                        temp = node;
                        node = temp->next;
                        temp->next = swap; 
                        swap = temp;

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

                List& slice(u64 start, u64 end) {

                    List *copy;
                    Node *node;

                    copy = new List();
                    node = nullptr;

                    if (dataCount < end) end = dataCount;

                    if (start < end) {

                        end = end - start;

                        node = &search(start);

                        while(!!end) {

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
                void puts(u64 index, T value, Args&&... arguments) {

                    if (dataCount < index) return;
                    else if (dataCount == index) push(value);
                    else put(index, value);

                    puts(index + 1, arguments...);
                }

                template<typename... Args>
                List& splice(u64 start, u64 deleteCount, Args&&... arguments) {

                    List *copy;

                    Node *node;
                    Node *temp;
                    Node *prev;

                    copy = new List();

                    node = nullptr;
                    temp = nullptr;
                    prev = nullptr;

                    if (dataCount < (start + deleteCount)) deleteCount = dataCount - start;

                    temp = &search(start);

                    while(!!deleteCount) {

                        node = temp;
                        temp = node->next;

                        prev = get_previous_ptr(node);

                        if (head == node) head = node->next;
                        if (tail == node) {
                            tail = prev;
                            tail->next = nullptr;
                        } else prev->next = node->next;

                        free(node);

                        deleteCount--;
                        dataCount--;
                    }

                    puts(start, arguments...);
                    return *copy;
                }

                T& operator[](u64 index) {

                    if (!(index < dataCount)) return (new Node())->data;

                    Node *node;

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

                    Node *node;
                    Node *temp;

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

    namespace Ex {

        template<typename T>
        class List {

            private:

                struct Node {

                    struct Node *previous;
                    struct Node *next;

                    T data;

                    Node(void) {

                        previous = nullptr;
                        next = nullptr;
                    }
                    ~Node() {}

                };

                struct NodeIterator {

                    Node *begin;
                    Node *end;

                    NodeIterator(void) {

                        begin = nullptr;
                        end = nullptr;
                        
                    }
                    ~NodeIterator() {}
                };

                Node *head;
                Node *midz;
                Node *tail;

                u64 dataCount;

                u64 getMiddlePos(void) {

                    return ((dataCount & 1) == 1 ? (dataCount + 1) / 2 : dataCount / 2) - 1;
                }

                u64 getMiddlePos(u64 m_size) {

                    return ((m_size & 1) == 1 ? (m_size + 1) / 2 : m_size / 2) - 1;
                }

                Node& middleSearchChild(u64 index, u64 m_size, NodeIterator nodeIterator) {

                    Node *node;
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

                Node& middleSearch(u64 index) {

                    Node *node;
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
                List& _concat(List& array, Args&&... arguments) {

                    List *copy;
                    List *temp;
                    Node *node;

                    copy = &(array.copy());
                    temp = &_concat(arguments...);

                    if (!(temp->dataCount > 0)) return *copy;
                    node = &(temp->first());

                    while (node != nullptr) {

                        copy->push(node->data);
                        node = node->next;
                    }

                    return *copy;
                }

                void put(u64 index, T value) {

                    Node *node;
                    Node *temp;

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
                
                ~List() {}

                void push(T value) {

                    Node *node;

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

                auto getitem(u64 index) {

                    Node *node;
                    ReturnType<T> rty;

                    rty.type = Type::FAIL;

                    if (index < dataCount) {

                        node = &middleSearch(index);

                        rty.type = Type::SUCCESS;
                        rty.data = node->data;
                    }

                    return rty;
                }

                void setitem(u64 index, T value) {

                    Node *node;

                    if (index < dataCount) {

                        node = &middleSearch(index);
                        node->data = value;
                    }
                }

                u64 size(void) {

                    return dataCount;
                }

                void remove(u64 index) {


                    Node *node;
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
                    Node *node;

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
                    Node *node;

                    node = tail;
                    value = node->data;
                    tail = node->previous;
                    tail->next = nullptr;

                    updateMiddleRightReduce();

                    free(node);
                    dataCount--;

                    return value;
                }

                auto indexOf(T value) {

                    Node *node;
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

                    Node *node;
                    Node *temp;
                    Node *swap;

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

                bool includes(T value) {

                    Node *node;

                    node = head;

                    while (node != nullptr) {

                        if (node->data == value) return true;

                        node = node->next;
                    }

                    return false;
                }

                List& slice(u64 start, u64 end) {

                    List *copy;
                    Node *node;

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
                void puts(u64 index, T value, Args&&... arguments) {

                    if (dataCount < index) return;
                    else if (dataCount == index) push(value);
                    else put(index, value);

                    puts(index + 1, arguments...);
                }

                template<typename... Args>
                List& splice(u64 start, u64 deleteCount, Args&&... arguments) {

                    List *copy;

                    Node *node;
                    Node *temp;
                    
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

                T& operator[](u64 index) {

                    if (!(index < dataCount)) return (new Node())->data;

                    Node *node;

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

                    Node *node;
                    Node *temp;

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
