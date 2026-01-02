#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int x = 10;

    int child_pid = fork();

    if (child_pid == 0) { // in child control
        std::cout << "Value of x in child: " << x << std::endl;
        x++; // creates a different copies in both child and parent. 
        std::cout << "Value of x after incrementing in the child: " << x << std::endl;
    } else {    // in the parent control
        std::cout << "Value of x in parent: " << x << std::endl;
        wait(NULL);
        std::cout << "Value of x after child finishes execution: " << x << std::endl;
    }

    return 0;
}
