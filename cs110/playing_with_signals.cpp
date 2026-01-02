#include <iostream>
#include <signal.h>
#include <unistd.h>

int *p;
void HandleSigSegv(int signal) {
    std::cout << signal << " Handled " << std::endl;
    sleep(1);
}

int main() {
    signal(SIGSEGV, &HandleSigSegv);

    p = nullptr;

    int r = *p;

    std::cout << "Value of r after sigsegv: " << r << std::endl;
    return 0;
}
