#include<iostream>
#include<math.h>

using namespace std;
#define LOG(x) cout << x << endl;

int multiply(void) {

    return 1;
}

template<typename T, typename... Args>
int multiply(T start, Args&&... arguments) {

    return start * multiply(arguments...);
}

// template<typename... Args>
// int multiply(Args&&... arguments) {

//     return (arguments * ...);
// }

// lambda

// auto logMessage = [this](const auto& e) { cout << e << endl; };
//                     |
//               like bind (capture)

int main(const int argc, const char** argv) {

    (void)argc;
    (void)argv;

    LOG(multiply<int>(1,2,3,4))

    LOG(pow(2,3))
    LOG(pow(16,0.5))

    return 0;
}
