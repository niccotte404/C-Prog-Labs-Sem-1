#include <stdio.h>

int main() {
    // initialize vars
    int num;
    char sym;

    // what user should do
    printf("Input integer number:");

    // scanning and printing int number
    scanf("%d", &num);
    printf("%d\n", num);

    // the same as previous but with char
    printf("Input a symbol:");
    scanf(" %c", &sym);
    printf("%c", sym);
}