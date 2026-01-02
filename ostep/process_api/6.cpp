#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int child_pid = fork();

    if (child_pid == 0) {
        return 111;
    } else {
        int status;
        waitpid(child_pid, &status, NULL);

        if (WIFEXITED(status)) {
            std::cout << WEXITSTATUS(status) << std::endl;
        }
    }
}
