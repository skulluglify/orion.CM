#pragma once
#ifndef _OE_TYPING_H_
#define _OE_TYPING_H_

typedef char* bytes;
typedef char** bytearray;
typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long int uint64;
typedef float f32;
typedef double f64;
typedef long double f128;

#define BYTE char
#define BYTES bytes
#define BYTEARRAY bytearray
#define CHAR char
#define CHARS char*
#define CHARACTER char
#define CHARACTERS char*
#define INTEGER int32
#define UINTEGER uint32
#define INTEGER64 int64
#define UINTEGER64 uint64
#define FLOAT f32
#define DOUBLE f64
#define FLOAT64 f64
#define BOOL bool
#define BOOLEAN bool

#define ui2 bool
#define i8 int8
#define ui8 uint8
#define i16 int16
#define ui16 uint16
#define i32 int32
#define ui32 uint32
#define i64 int64
#define ui64 uint64

#define fn void

#ifdef __cplusplus

/* CPP SOURCE CODE */
#include <iostream>
#define LOG(x) std::cout << "\x1b[1;33;40m[DEBUG]: \x1b[1;32;40m" << x << "\x1b[0m" << std::endl; // 27

#endif

#endif /*_OE_TYPING_H_*/