#include <stdio.h>

int main() {
    //initializing
    int num;
    int num2;

    // task 1 scanning num in hex
    printf("Task1:");
    scanf("%x", &num);

    //task 2 printing num in oct
    printf("Task2: %o\n", num);

    //printing num in hex with moved 2 bits
    printf("Task3: %x ", num);
    printf("%x\n", num<<2);

    //printing num in hex with negative bit
    printf("Task4: %x ", num);
    printf("%x\n", ~num);

    // scanning num2 && bit comparison num1 with num2
    printf("Task5:");
    scanf("%x", &num2);
    printf("%x", num | num2);

    return 0;
}
