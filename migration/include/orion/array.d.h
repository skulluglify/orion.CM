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

                auto& getitem(T value);

                void setitem(T value);

                u64 size(T value);

                void remove(u64 index);

                List& copy(void);

                template<typename... Args>
                List& concat(Args&&... arguments);

                auto& first(void);

                auto& top(void);

                T shift(void);
                
                T pop(void);

                auto& indexOf(T value);

                List& reverse(void);

                bool includes(T value);

                List& slice(u64 start, u64 end);

                void put(u64 index, T value);

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
        class List {};
    };

}
#endif

#endif
