#include <iostream>
#include <unistd.h>

int main() {
    int fds[2];
    pipe(fds);

    int child_pid = fork();

    // 0 read, 1 write
    if (child_pid == 0) {
        close(fds[0]);

        std::cout << "Hello" << std::endl;
        char c = 'x';
        write(fds[1], &c, 1);
        close(fds[1]);
    } else {
        close(fds[1]);

        char c;
        read(fds[0], &c, 1);
        std::cout << "Good bye! " << c << std::endl;
        close(fds[0]);
    }

    return 0;
}
