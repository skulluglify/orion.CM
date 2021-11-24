#include<iostream>
#include<thread>
#include<mutex>

std::recursive_mutex rm;
std::mutex m;

int buffer = 0;

void WorkRecur(int value) {

    if (value == 0)
        return;

    rm.lock();
    
    std::cout << "value at: " << value << std::endl; 
    WorkRecur(value - 1);

    rm.unlock();
}

void DoWork(int index) {

    m.lock();

    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(1s);

    std::cout << "Started " << index << " Thread By Id: " << std::this_thread::get_id() << std::endl;

    // index = index * 6000;
    // while (index != 0)
        // index--;

    WorkRecur(10);

    m.unlock();
}

int main(const int argc, const char** argv) {

    (void)argc;
    (void)argv;

    std::cout << std::thread::hardware_concurrency() << std::endl;

    for (int i = 0; i < (int)std::thread::hardware_concurrency(); i++) {    
        std::thread worker(DoWork, i);
        worker.join();
    }

    std::cout << "end program" << std::endl;

    return 0;
}
