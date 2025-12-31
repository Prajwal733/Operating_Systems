#include <iostream>
#include <unistd.h>

int main() {
    int pid = fork();

    for (char a='a';a<='z';a++) {
        std::cout << a << std::endl;
        if (pid != 0)
            sleep(1);
    }

    return 0;
}
