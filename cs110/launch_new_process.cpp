#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();

    if (pid == 0) {
        char* argv[] = {(char*)"./simple_prog", nullptr};
        int return_value = execvp(argv[0], argv);

        if (return_value == -1) {
            std::cout << "Cannot run simple prog" << std::endl;
        }
    } else {
        std::cout << "hi from the parent process" << std::endl;
        waitpid(-1, NULL, 0);
    }
    
    return 0;
}
