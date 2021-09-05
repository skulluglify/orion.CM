#pragma once
#ifndef _YELP_H_
#define _YELP_H_

// y extension like python

#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>

using namespace std;

typedef const char* bytes;
typedef unsigned char uchar;
typedef short int8;
typedef long int32;
typedef long long int64;
typedef unsigned short uint8;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef float float32;
typedef double float64;
typedef long double float128;

// typedef chrono::time_point<chrono::_V2::system_clock, chrono::duration<long int, ratio<1, 1000000000> > > durations;

namespace yelp 
{
    namespace time 
    {
        typedef chrono::time_point<chrono::_V2::system_clock, chrono::duration<long int, ratio<1, 1000000000> > > durations;
        time::durations performance_now ();
        float32 duration_cast (time::durations start, time::durations end);
    }
    void init();
    void sleep(float32 seconds);
    char chr (uint8 i);
    uint8 ord (char c);
}

#endif
