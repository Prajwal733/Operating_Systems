#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using std::cin;
using std::cout;
using std::string;

int main() {
    int fds[2];
    pipe(fds);

    int child_pid = fork();
    // 0 for reading 1 for writing

    if (child_pid == 0) {
        close(fds[0]);

        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);

        cout << "Hifromchild" << std::endl;
    } else {
        close(fds[1]);

        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);

        string s;
        cin>>s;

        cout << "Received at the parent: " << s << std::endl;
        wait(NULL);
    }

    return 0;
}
