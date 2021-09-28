CXX = /usr/bin/g++
CFLAGS = -std=gnu++17 -Wall -Wextra -Werror -Wunused-parameter -Wunused-variable -Wpedantic -Wsign-compare -O3 -fpic -fno-plt

all: build

debug: build
	clear && ./build/main.o

build: clean
	mkdir -p build/extensions
	mkdir -p build/modules
	mkdir -p build/wasm
	$(CXX) $(CFLAGS) -o build/yelp.o -c extras/yelp.cpp
	$(CXX) $(CFLAGS) -o build/orion.o -c extras/orion.cpp
	$(CXX) $(CFLAGS) -o build/main.o -c main.cpp
#	g++ -shared -Wl,-soname,liborion.so.1 -o build/liborion.so.1.0 build/orion.o build/yelp.o
#	g++ -Wall -Wextra -Werror -fPIC -L`pwd`/build/liborion.so.1.0 -lorion -o build/main.pack.o -c main.cpp -static
	$(CXX) $(CFLAGS) -o build/main.pack.o build/main.o build/orion.o build/yelp.o -static
	rm -rf build/main.o build/yelp.o build/orion.o
	mv build/main.pack.o build/main.o
	chmod +x ./build/main.o

clean:
	rm -rf ./build
