#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <chrono>

constexpr int kIterations = 100000;

int main() {
    long long sum_of_time_in_micro_seconds = 0;
    
    int fd = open("./open.txt", O_RDONLY | O_CREAT, 0777);
    int write_fd = open("./close.txt", O_WRONLY | O_CREAT, 0777);

    for (int i=0;i<kIterations;i++) {
        char buf;
        auto start = std::chrono::steady_clock::now();
        read(fd, &buf, 1);
        auto end = std::chrono::steady_clock::now();

        write(write_fd, &buf, 1);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        sum_of_time_in_micro_seconds += duration.count();
    }

    std::cout << "Average duration: " << (sum_of_time_in_micro_seconds / kIterations) << std::endl;
    close(fd);
    close(write_fd);

    return 0;
}

/*
 108 micro seconds. 
*/
