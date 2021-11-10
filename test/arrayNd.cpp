#include<iostream>
#include<string>
#include<array>

int main(int argc, const char** argv) {

    (void)argc;
    (void)argv;

    // array3d
    int* a = new int[4 * 4 * 4];

    int x, y, z;

    x = 3;
    y = 2;
    z = 1;
    
    *(a + (x * 4 * 4) + (y * 4) + z) = 64;

    std::cout << *(a + (x * 4 * 4) + (y * 4) + z) << std::endl;

    // array2d
    int* b = new int[4 * 4];

    x = 2;
    y = 1;
    
    *(b + (x * 4) + y) = 64;

    std::cout << *(b + (x * 4) + y) << std::endl;

    return 0;
}
