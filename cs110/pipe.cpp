#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fds[2];
    pipe(fds);

    int pid = fork();
    if (pid == 0) { // child
        // fds[0] -> read, fds[1] -> write 
        close(fds[1]);

        char buffer[10];
        read(fds[0], buffer, 10);

        std::cout << "From child " << getpid() << " " << buffer << std::endl;
        close(fds[0]);
    } else { // parent 
        close(fds[0]);

        char buffer[] = "Prajwal";
        write(fds[1], buffer, 7);

        waitpid(pid, NULL, 0);
        close(fds[1]);
    }

    return 0;
}
