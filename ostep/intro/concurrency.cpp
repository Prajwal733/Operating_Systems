#include <iostream>
#include <thread>

volatile int counter = 0;

void Thread(int loop) {
    for (int i=0;i<loop;i++) {
        counter++;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Invalid usage" << std::endl;
        return 0;
    }

    int loop = atoi(argv[1]);
    std::cout << "loop: " << loop << std::endl;
    std::thread t1(&Thread, loop);
    std::thread t2(&Thread, loop);

    t1.join();
    t2.join();

    std::cout << "Final value: " << counter << std::endl;
    return 0;
}
