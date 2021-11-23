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

    namespace se {

        namespace abs {

            enum Type {

                FAIL,
                SUCCESS,
            };

            template<typename T>
            struct ReturnType {

                int type;
                T data;

                T valueOf(void) {

                    return data;
                }

            };

        };
        
    };

}
#endif

#endif
