#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int child_pid = fork();

    if (child_pid == 0) {
        std::cout << "Child starts execution" << std::endl;
        close(STDOUT_FILENO);
        std::cout << "Hello from the child" << std::endl;
    } else {
        wait(NULL);
        std::cout << "Parent completes" << std::endl;
    }

    return 0;
}
