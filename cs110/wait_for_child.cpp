#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();

    if (pid == 0) {
        std::cout << "Bye from the child " << std::endl;
        sleep(15);
        return 110;
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            std::cout << "Child exited with the status " << WEXITSTATUS(status) << std::endl;
        } else {
            std::cout << "Child terminated abnormally" << std::endl;
        }
    }

    return 0;
}

/*
Output: 
Bye from the child 
Child exited with the status 110
*/
