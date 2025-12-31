#include <iostream>
#include <unistd.h>

int main() {
    pid_t id = getpid();

    std::cout << "Process id is " << id << std::endl;

    pid_t pid = fork();

    if (pid != 0) {
        std::cout << "Hello from the parent with process id: " << getpid() << std::endl;
        std::cout << "Child id must be equal to: " << pid << std::endl;
    } else {
        std::cout << "Hello from the child with process id: " << getpid() << " parent id " << getppid() << std::endl;
    }

    return 0;
}
