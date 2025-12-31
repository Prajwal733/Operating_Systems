#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int num_done = 0;
constexpr int KNumChild = 5;

// If multiple signal occur almost at the same time, kernel race condition can happen and 
// handler will run only once, so if all the children sleep for same time, this program can 
// run infinetly. 
void HandleChildState(int signal) {
    std::cout << "Signal " << signal << std::endl;
    waitpid(-1, NULL, 0);
    num_done++;
}

void Child(int time) {
    sleep(time);
    std::cout << "child tired of playing" << std::endl;
}

int main() {
    signal(SIGCHLD, HandleChildState); // SIGCHLD will be passed to HandleChildState

    for (int i=0;i<KNumChild;i++) {
        int pid = fork();

        if (pid == 0) {
            Child(i + 1);
            return 0;
        }
    }

    while (num_done < KNumChild) {
        std::cout << "Atleast one of the child is still playing, going to sleep" << std::endl;
        sleep(2);
        std::cout << "Dad wakes up" << std::endl;
    }

    std::cout << "Going home" << std::endl;
    return 0;
}
// Signal 17 is SIGCHLD
