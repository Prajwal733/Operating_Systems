#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

void WriteToFile(int fd, char* buffer) {
    
    int bytes_to_write = strlen(buffer);
    std::cout << buffer << " " << bytes_to_write << std::endl;
    int bytes_written = 0;

    while (bytes_written < bytes_to_write) {
        int written = write(fd, buffer + bytes_written, bytes_to_write - bytes_written);

        std::cout << "Written " << written << std::endl;
        if (written < 0) {
            std::cout << "Problem occured while writing" << std::endl;
            return;
        }

        bytes_written += written;
    }
}

int main() {
    int fd = open("./output.txt", O_WRONLY | O_CREAT, 0644);

    int child_pid = fork();

    if (child_pid == 0) {
        for (int i=0;i<100;i++) {
            char buffer[] = "Message from child\n\0";
            WriteToFile(fd, buffer);
        }
        close(fd);
    } else {
        for (int i=0;i<100;i++) {
            char buffer[] = "Message from parent\n\0";
            WriteToFile(fd, buffer);
        }
        close(fd);

        wait(NULL);
        std::cout << "Program completes" << std::endl;
    }

    return 0;
}
