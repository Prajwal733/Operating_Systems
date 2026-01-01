#include <stdio.h>
#include <unistd.h>

void main(int argc, char* argv[]) {
    printf("%d\n", argc);
    if (argc != 2) {
        printf("Incorrect usage");
        return;
    } else {
        printf("Correct usage\n");
    }

    printf("Entering while loop\n");
    while (1) {
        sleep(1);
        printf("%s\n", argv[1]);
    }
}

/*
Output:
./a.out "A" & ./a.out "B" & ./a.out "C" & ./a.out "D" & ./a.out "E"
[1] 1898
[2] 1899
[3] 1900
[4] 1901
2
2
2
Correct usage
Correct usage
Entering while loop
2
2
Entering while loop
Correct usage
Correct usage
Entering while loop
Correct usage
Entering while loop
Entering while loop
D
B
C
E
A
E
C
B
D
A
C
A
E
B
D
A
C
B
D
E
B
C
A
E
D
*/
