#include <iostream>
#include <fcntl.h>
#include <unistd.h>

class FileManager {
public:
    FileManager(char* argv, int flags, int mode = 0 /*default*/) {
        fd_ = open(argv, flags, mode);
    }

    ~FileManager() {
        close(fd_);
    }

    FileManager(FileManager& other) = delete;
    FileManager& operator = (FileManager& other) = delete;

    int GetFileDescriptor() {
        return fd_;
    }

private:
    int fd_;
};

// compile time constant
constexpr int kReadBytes = 1024;

int main(int argc, char* argv[]) {
    FileManager read_file(argv[1], O_RDONLY), write_file(argv[2], O_WRONLY | O_CREAT, 0644);

    char buffer[kReadBytes];

    while (true) {
        ssize_t read_bytes = read(read_file.GetFileDescriptor(), buffer, kReadBytes);

        if (!read_bytes) {
            break;
        }

        ssize_t written_bytes = 0;
        while (written_bytes < read_bytes) {
            ssize_t current_write = write(write_file.GetFileDescriptor(), buffer + written_bytes, read_bytes - written_bytes);
            if (current_write == -1) {
                std::cout << "Error while writing to the file" << std::endl;
                return 1;
            }

            written_bytes += current_write;
        }
    }

    std::cout << "Operation complete" << std::endl;
    return 0;
}
