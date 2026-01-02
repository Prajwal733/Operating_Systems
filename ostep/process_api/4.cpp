#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int child_pid = fork();

    if (child_pid == 0) {
        char* arg[] = {(char*)"/bin/ls", nullptr};
        execv(arg[0], arg);
    } else {
        wait(NULL);
    }

    return 0;
}
