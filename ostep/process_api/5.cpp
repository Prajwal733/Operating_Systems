#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int child_pid = fork();

    if (child_pid == 0) {
        int id = wait(NULL); // returns -1 when there is no process to wait for. 
        std::cout << id << " " << "Child finishes" << std::endl;
    } else {
        int id = wait(NULL);
        std::cout << (id == child_pid) << " " << "Parent finishes" << std::endl;
    }

    return 0;
}
