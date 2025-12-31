#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i=0;i<10;i++) {
        int pid = fork();

        if (pid == 0) {
            sleep(10 - i);
            return 110 + i;
        }
    }

    for (int i=0;i<10;i++) {
        int status;
        waitpid(-1, &status, 0);

        if (WIFEXITED(status)) {
            std::cout << WEXITSTATUS(status) << std::endl;
        } else {
            std::cout << "one of the child terminated abnormally" << std::endl;
        }
    }

    return 0;
}

/*
Output:
119
118
117
116
115
114
113
112
111
110
*/
