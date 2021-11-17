#pragma once
#ifndef __ORION_ARRAY_DECLARE__
#define __ORION_ARRAY_DECLARE__

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

                    Node(void) {}
                    ~Node(void) {}
                };

                struct NodeIterator {
                    
                    Node* begin;
                    Node* end;

                    NodeIterator(void) {}
                    ~NodeIterator(void) {}
                };

                Node* head;
                Node* midz;
                Node* tail;
                
                ui64 count;

                ui64 GetMiddlePos(ui64 Size);

                Node* MiddleSearchChild(uint32_t Size, ui64 index, NodeIterator nodeIterator);

                Node* MiddleSearch(ui64 index);

                void UpdateMiddleReduce(void);

                void UpdateMiddleReduceRight(void);

                void UpdateMiddleReduceLeft(void);

                List& ConcatConceptMultiply(void);

                template<typename... Args>
                List& ConcatConceptMultiply(List& current, Args&&... arguments);

            public:

                List(void) {}
                
                ~List(void) {}

                void Push(T data);

                ReturnType<T> GetItem(ui64 index);

                void SetItem(ui64 index, T data);

                ui64 Size(void);

                void Remove(ui64 index);

                List& Copy(void);

                template<typename... Args>
                List& Concat(Args&&... arguments);

                Node& Bottom(void);

                Node& Top(void);

                T Shift(void);

                T Pop(void);

                ReturnType<ui64> GetIndexOf(T data);

                void Reverse(void);

                bool Includes(T data);

                // slice (index)start, (count)length
                // splice (index)start, (count)delete, (data)put
        };

    };

}

#endif
#endif
