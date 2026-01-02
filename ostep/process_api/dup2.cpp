#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main() {
    /*
    FD open file
    0  STDIN_FILENO
    1  STDOUT_FILENO
    2  STDERR_FILENO
    */

    int fd = open("logs2.txt", O_WRONLY | O_CREAT, 0777); // returns lowest available fd which is 3. 
    /*
    FD open file
    0  STDIN_FILENO
    1  STDOUT_FILENO
    2  STDERR_FILENO
    3  logs2.txt
    */
    std::cout << fd << std::endl; // prints 3 
    dup2(fd, STDOUT_FILENO); // this first closes file pointed by STDOUT_FILENO then makes STDOUT_FILENO to points to logs2.txt
    /*
    FD open file
    0  STDIN_FILENO
    1  log2.txt
    2  STDERR_FILENO
    3  logs2.txt
    */
    std::cout << fd << std::endl; // prints 3 
    close(fd); // closes 3 entry
    /*
    FD open file
    0  STDIN_FILENO
    1  log2.txt
    2  STDERR_FILENO
    */
    std::cout << "Hello world " << fd << std::endl; // cout points to file descriptor 1 so prints to logs2.txt

    return 0;
}
