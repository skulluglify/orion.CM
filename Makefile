debug: clean build
	clear && ./build/bundle.o

build:
	mkdir -p build
	g++ -Wall -Wextra -Werror -o build/yelp.o -c extras/yelp.cpp
	g++ -Wall -Wextra -Werror -o build/orion.o -c extras/orion.cpp
	g++ -Wall -Wextra -Werror -o build/main.o -c main.cpp
	g++ -Wall -Wextra -Werror -o build/bundle.o build/main.o build/orion.o build/yelp.o -static
	rm -rvf build/main.o build/yelp.o build/orion.o
	chmod +x ./build/bundle.o

clean:
	rm -rvf ./build
