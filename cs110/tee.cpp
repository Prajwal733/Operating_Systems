#include <iostream>
#include <fcntl.h>
#include <unistd.h>

bool WriteAll(const char* buffer, int write_bytes, int file_des) {
    int written = 0;
    while (written < write_bytes) {
        ssize_t current_write = write(file_des, buffer, write_bytes - written);

        if (current_write == -1) {
            return false;
        }

        written += current_write;
    }

    return true;
}

constexpr int kReadBytes = 1024;

int main(int argc, char* argv[]) {
    int fds[argc];
    fds[0] = STDOUT_FILENO;

    for (int i=1;i<argc;i++) {
        fds[i] = open(argv[i], O_WRONLY | O_CREAT, 0644);
    }

    char buffer[kReadBytes];
    while (true) {
        ssize_t read_bytes = read(STDIN_FILENO, buffer, kReadBytes);

        if (!read_bytes)
            break;

        for (int i=0;i<argc;i++) {
            bool success = WriteAll(buffer, read_bytes, fds[i]);

            if (!success) {
                std::cout << "Error while writing to a file" << std::endl;
                break;
            }
        }
    }

    for (int i=1;i<argc;i++) {
        close(fds[i]);
    }

    std::cout << "end of the operation" << std::endl;
    return 0;
}
