CXX = /usr/bin/g++
CFLAGS = -std=gnu++17 -Wall -Wextra -Werror -Wunused-parameter -Wunused-variable -Wpedantic -Wsign-compare -O3 -fpic -fno-plt

all: build

debug: build
	clear && ./build/main.o

build: clean playground
	$(CXX) $(CFLAGS) -o build/main.o main.cpp

playground:
	mkdir -p build/extensions
	mkdir -p build/modules
	mkdir -p build/wasm

clean:
	rm -rf ./build
