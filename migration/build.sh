#! /usr/bin/env bash

MAIN="test.string"

CFLAGS="-Wall -Wextra -Werror -Wunused-parameter -Wunused-variable -Wpedantic -Wsign-compare -O3 -fpic -fno-plt"

/usr/bin/g++ -std=gnu++17 $CFLAGS -o $MAIN.o $MAIN.cpp
