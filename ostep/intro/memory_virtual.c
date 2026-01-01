#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main() {
    int* p = (int *)malloc(sizeof(int));

    printf("Allocated memory address %p\n", p);
    while (1) {
        sleep(1);
        printf("%d [%d]\n", *p, getpid());
        (*p)++;
    }
}

/*
[1] 24113
[2] 24114
(24113) address pointed to by p: 0x200000
(24114) address pointed to by p: 0x200000
(24113) p: 1
(24114) p: 1
(24114) p: 2
(24113) p: 2
(24113) p: 3
(24114) p: 3
(24113) p: 4
(24114) p: 4
*/
