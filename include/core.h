#pragma once
#ifndef __ORION_CORE__
#define __ORION_CORE__

#ifdef __cplusplus

#include<string>

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long int i64;

typedef unsigned char ui8;
typedef unsigned short ui16;
typedef unsigned int ui32;
typedef unsigned long long int ui64;

typedef float f32;
typedef double f64;
typedef double long f128;

extern "C++" {

    typedef struct {

        std::string type;
        ui8 *pointer;

    } ReturnType;

    namespace Ex {



    };

}

#endif
#endif
