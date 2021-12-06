#pragma once
#ifndef ORION_DEBUG_H
#define ORION_DEBUG_H

#include<iostream>

#ifndef PRODUCTION
    #define LOG(x) std::cout << x << std::endl;
    #define BS(x) std::cout << std::bitset<8>(x) << std::endl;
#else
    #define LOG(x)
    #define BS(x)
#endif

#ifdef __cplusplus
extern "C++" {

    // pass

}
#endif

#endif
