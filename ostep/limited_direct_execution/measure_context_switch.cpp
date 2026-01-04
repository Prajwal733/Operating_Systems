#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <sys/wait.h>

constexpr int kIterations = 100;

int main() {
    cpu_set_t mask;

    CPU_ZERO(&mask);
    CPU_SET(0, &mask);

    sched_setaffinity(getpid(), sizeof(mask), &mask);

    int p2c[2], c2p[2]; // first array, parent writes c reads vice versa
    pipe(p2c);
    pipe(c2p);

    int child_pid = fork();
    if (child_pid == 0) {
        close(p2c[1]);
        close(c2p[0]);

        for (int i=0;i<kIterations;i++) {
            std::string s = "HiFromchil";
            write(c2p[1], s.c_str(), s.size());

            char buf[10];
            read(p2c[0], &buf, 10);
        }

        close(c2p[1]);
        close(p2c[0]);
    } else {
        auto start = std::chrono::steady_clock::now();
        close(p2c[0]);
        close(c2p[1]);
        for (int i=0;i<kIterations;i++) { // one iteration 2 contex switches
            char buf[10];
            read(c2p[0], &buf, 10);

            std::string s = "HiFrompars";
            write(p2c[1], s.c_str(), s.size());
        }
        close(c2p[0]);
        close(p2c[1]);

        wait(NULL);
        auto end = std::chrono::steady_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Average operation: " << (duration.count() / (2 * kIterations)) << std::endl;
    }

    return 0;
}
