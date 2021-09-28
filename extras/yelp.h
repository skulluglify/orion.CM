#pragma once
#ifndef _YELP_H_
#define _YELP_H_

// y extension like python

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

// long == signed long int
// long long == signed long long int

typedef const char* bytes;
typedef short int8;
typedef int int32;
typedef long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef float float32;
typedef double float64;
typedef long double float128;

typedef bytes BYTES;
typedef char CHAR;
typedef int32 INTEGER;
typedef uint32 UINTEGER;
typedef int64 INTEGER64;
typedef uint64 UINTEGER64;
typedef float32 FLOAT;
typedef float64 FLOAT64;
typedef float128 FLOAT128;
typedef bool BOOLEAN;

typedef void fn;

// typedef chrono::time_point<chrono::_V2::system_clock, chrono::duration<long int, ratio<1, 1000000000> > > durations;

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

    string bin (uint8 n);

    // string bin (uint16 n);

    // string bin (uint32 n);

    // string bin (uint64 n);
}

#endif
