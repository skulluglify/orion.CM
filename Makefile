debug: build
	clear && ./build/main.o

build: clean
	mkdir -p build/extensions
	g++ -Wall -Wextra -Werror -Wunused-parameter -o build/yelp.o -c extras/yelp.cpp
	g++ -Wall -Wextra -Werror -Wunused-parameter -o build/orion.o -c extras/orion.cpp
	g++ -Wall -Wextra -Werror -Wunused-parameter -o build/main.o -c main.cpp
#	g++ -shared -Wl,-soname,liborion.so.1 -o build/liborion.so.1.0 build/orion.o build/yelp.o
#	g++ -Wall -Wextra -Werror -fPIC -L`pwd`/build/liborion.so.1.0 -lorion -o build/AppBundleMainPackage.o -c main.cpp -static
	g++ -fpic -fno-plt -o build/AppBundleMainPackage.o build/main.o build/orion.o build/yelp.o -static
	rm -rf build/main.o build/yelp.o build/orion.o
	mv build/AppBundleMainPackage.o build/main.o
#	chmod +x ./build/AppBundleMainPackage.o
	chmod +x ./build/main.o

clean:
	rm -rf ./build
