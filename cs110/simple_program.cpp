#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Hi from simple program" << std::endl;
    for (int i=0;i<argc;i++) {
        std::cout << argv[i] << std::endl;
    }

    return 0;
}
