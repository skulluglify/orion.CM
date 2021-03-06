#pragma once
#ifndef _ORION_ARRAY_H
#define _ORION_ARRAY_H

#include"dtype.h"
#include"debug.h"

#define Type se::abs::Type
#define ReturnType se::abs::ReturnType

#ifdef __cplusplus
extern "C++" {
    
    namespace Se {

        template<typename T>
        class List {

            public:

                List(void);
                
                ~List();

                void push(T value);

                auto getitem(u64 index);

                void setitem(u64 index, T value);

                u64 size(void);

                void remove(u64 index);

                List& copy(void);

                template<typename... Args>
                List& concat(Args&&... arguments);

                auto& first(void);

                auto& top(void);

                T shift(void);
                
                T pop(void);

                auto indexOf(T value);

                List& reverse(void);

                bool includes(T value);

                List& slice(u64 start, u64 end);

                void puts(u64);

                template<typename... Args>
                void puts(u64 index, T value, Args&&... arguments);

                template<typename... Args>
                List& splice(u64 start, u64 deleteCount, Args&&... arguments);

                T& operator[](u64 index);

                template<typename _Cast>
                void display(void);

                void destroy(void);

            // public
        };
    };

    namespace Ex {

        template<typename T>
        class List {

            public:

                List(void);
                
                ~List();

                void push(T value);

                auto getitem(u64 index);

                void setitem(u64 index, T value);

                u64 size(void);

                void remove(u64 index);

                List& copy(void);

                template<typename... Args>
                List& concat(Args&&... arguments);

                auto& first(void);

                auto& top(void);

                T shift(void);
                
                T pop(void);

                auto indexOf(T value);

                List& reverse(void);

                bool includes(T value);

                List& slice(u64 start, u64 end);

                void puts(u64);

                template<typename... Args>
                void puts(u64 index, T value, Args&&... arguments);

                template<typename... Args>
                List& splice(u64 start, u64 deleteCount, Args&&... arguments);

                T& operator[](u64 index);

                template<typename _Cast>
                void display(void);

                void destroy(void);

            // public
        };
    };

}

#endif

#endif
