#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void countUp() {
    for (int i = 1; i <= 20; ++i) {
        mtx.lock();
        std::cout << "Count Up: " << i << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // For demonstration purpose
    }
}

void countDown() {
    for (int i = 20; i >= 0; --i) {
        mtx.lock();
        std::cout << "Count Down: " << i << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // For demonstration purpose
    }
}

int main() {
    std::thread t1(countUp);
    std::thread t2(countDown);

    t1.join();
    t2.join();

    return 0;
}