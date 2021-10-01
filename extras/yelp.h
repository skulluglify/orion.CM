#pragma once
#ifndef _YELP_H_
#define _YELP_H_

// y extension like python

#ifdef __cplusplus

#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <bitset>
#include <limits>
#include <string>

#define TRUE 1
#define FALSE 0

using namespace std;

typedef char* bytes;
typedef char** bytearray;
typedef short int8;
typedef int int32;
typedef long long int int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long int uint64;
typedef float float32;
typedef double float64;
typedef long double float128;

#define BYTES bytes
#define BYTEARRAY bytearray
#define CHAR char
#define INTEGER int32
#define UINTEGER uint32
#define INTEGER64 int64
#define UINTEGER64 uint64
#define FLOAT float32
#define FLOAT64 float64
#define DOUBLE float64
#define FLOAT128 float128
#define BOOL bool

#define i32 int32
#define ui32 uint32
#define i64 int64
#define ui64 uint64
#define f32 float32
#define f64 float64
#define f128 float128

#define fn void

namespace yelp 
{
    namespace time 
    {
        typedef chrono::time_point<chrono::_V2::system_clock, chrono::duration<UINTEGER, ratio<1, 1000000000> > > durations;
        
        time::durations performance_now ();
        
        FLOAT duration_cast (time::durations start, time::durations end);
    }
    
    fn init();
    
    fn sleep(FLOAT seconds);
    
    char chr (uint8 i);
    
    uint8 ord (char c);

    template<typename T>
    string bin (T n) 
    {
        const size_t N = sizeof(T);
        return bitset<N*8>(n).to_string();
    }
}

#endif
#endif /*_YELP_H_*/
