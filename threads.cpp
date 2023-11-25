#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m; //variable for mutex
std::condition_variable c;
bool ready = false;

//method to count up to 20
void countingUp() {
    for (int i = 1; i <= 20; ++i) {  //iterations set to 20
        m.lock(); //sets as current thread
        std::cout << "Counting Up: " << i << std::endl;
        if (i == 20) {
            ready = true;
            c.notify_one(); // As this hits 20 it will communicate with other thread
        }
        m.unlock(); //frees thread
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); //delay
    }
}

//method to count down to 0
void countingDown() {
    std::unique_lock<std::mutex> lock(m);
    c.wait(lock, [] {return ready;});

    for (int i = 19; i >= 0; --i) { //iterates until it counts to 0
        std::cout << "Counting Down: " << i << std::endl; //will count down with current number
        std::this_thread::sleep_for(std::chrono::milliseconds(100));// delay
    }
}

//main program that tests the methods
int main() {
	std::cout << "|||--Program Start--|||" <<  std::endl;

    std::thread t1(countingUp); //thread 1
    std::thread t2(countingDown); //thread 2

    t1.join();
    t2.join();

    std::cout << "|||--Program End--|||" << std::endl;

    return 0;
}
