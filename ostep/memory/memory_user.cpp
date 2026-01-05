#include <iostream>
#include <sys/wait.h>

constexpr long long kArrayLength = 1000000000;

int arr[kArrayLength];

int main() {
    std::cout << getpid() << std::endl;

    for (int i=0;i<kArrayLength;i++) {
        arr[i] = i;
        sleep(0.01);
    }

    return 0;
}
