#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

void CheckAndPrintStatus(int status) {
    if (WIFEXITED(status)) {
        std::cout << "Good: " << WEXITSTATUS(status) << std::endl;
    } else {
        std::cout << "Abnormal termination" << std::endl;
    }
}

void HandleSegmentationFault(int status) {
    std::cout << "Just handling " << status << std::endl;
}

int main() {
    signal(SIGSEGV, HandleSegmentationFault);

    int pid1 = fork();
    if (pid1 == 0) { // child 1. 
        raise(12);
    }

    int pid2 = fork();

    if (pid2 == 0) { // child 2. 
        sleep(100);
        return 0;
    }

    int status;
    waitpid(pid1, &status, 0);
    CheckAndPrintStatus(status);

    kill(pid2, 10);
    waitpid(pid2, &status, 0);
    CheckAndPrintStatus(status);

    kill(getpid(), 11);

    std::cout << "Continuing execution " << std::endl;
    return 0;
}
