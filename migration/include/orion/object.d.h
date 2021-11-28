#pragma once
#ifndef _ORION_OBJECT_H
#define _ORION_OBJECT_H

#include<string>

#include"dtype.h"
#include"debug.h"
#include"array.h"

#ifdef __cplusplus
extern "C++" {

    // pass
    namespace Ex {

        template<typename T>
        class Dict {

            public:

                Dict(void);

                ~Dict();

                void setitem(const char* key, const T& value);

                T& getitem(const char* key);
                
                T& operator[] (const char* key);

                bool find(const char* key);

                auto& keys(void);
            
            // public
        };
    };

}
#endif

#endif
