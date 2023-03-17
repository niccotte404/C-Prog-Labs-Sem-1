#include <stdio.h>

int main() {
    // initializing
    int num;
    int num2;

    // scanning num && is num between -77 and 1
    printf("Input number:");
    scanf("%d", &num);
    int bool = (-77 <= num) * (num <= 1);
    char * x = bool ? "True" : "False";
    printf("%s\n", x);

    // scanning num2 && searching 18th bit
    printf("Input number:");
    scanf("%x", &num2);
    printf("%d", (num2 >> 18) & 1);
    return 0;
}
