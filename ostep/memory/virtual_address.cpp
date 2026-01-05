#include <iostream>

int main() {
    printf("%p\n", main); // address of the main. 
    int* p = new int(8);
    printf("%p\n", p);
    int x = 10;
    printf("%p\n", &x);

    return 0;
}

/*
    output:
        0x5ef837755189
        0x5ef849dba6c0
        0x7ffe40c4074c
*/
