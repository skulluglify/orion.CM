#pragma once
#ifndef ORION_DTYPE_H
#define ORION_DTYPE_H

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long int i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long int u64;

typedef float f32;
typedef double f64;
typedef double long f128;

#ifdef __cplusplus
extern "C++" {

    namespace Se {

        namespace Abstract {

            enum Type {

                NONE     = 0x00,
                EMPTY    = 0x00,
                FAIL     = 0x00,
                SUCCESS  = 0x20,
                NUMBER   = 0x01,
                INFINITE = 0x02,
                ARRAY    = 0xA0,
                STRING   = 0xA1,
                SYMBOL   = 0xA2,
                OBJECT   = 0xB0,
                FUNCTION = 0xC0,
            };

            template<typename T>
            struct ReturnType {

                int type;
                T data;

                T valueOf(void) {

                    return data;
                }

            };

            // TODOs
            // VarType
            // built in Cast Int Pointer

        };
        
    };

}
#endif

#endif
