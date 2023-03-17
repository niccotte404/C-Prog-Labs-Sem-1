#include <stdio.h>
#include <string.h>

int main() {

    // Task 1	Осуществить конкатенацию (сложение) двух строк
    int s;
    printf("Task 1:\n");
    scanf("%d", &s);
    char str1[s+s], str2[s];
    scanf("%s", &*str1);
    scanf("%s", &*str2);

    strcat(str1, str2);
    printf("%s\n", str1);

    // Task 4	Осуществить сравнение первых n символов двух строк.
    int n;
    printf("Task 4:\n");
    scanf("%d", &n);
    int k = strncmp(str1, str2, n);
    if (k > 0){
        printf("%s\n", str1);
    }
    else{
        printf("%s\n", str2);
    }

    // Task 5   Осуществить копирование одной строки в другую строку
    char str1copy[s];
    printf("Task 5:\n");
    strcpy(str1copy, str1);
    printf("%s %s\n", str1, str1copy);

    // Task 8	Осуществить поиск в строке первого вхождения указанного символа
    char c;
    int p;
    printf("Task 8:\n");
    scanf("%d", &p);
    char str[p];
    scanf("%s", &*str);
    scanf(" %c", &c);
    char * ind = strchr(str, c);
    if (ind) {
        printf("%d\n", ind - str);
    }
    else {
        printf("The character was not found\n");
    }

    // Task 11	Определить длину отрезка одной строки, содержащего символы из множества символов, входящих во вторую строку.
    int ln, l, l2;
    printf("Task 11:\n");
    scanf("%d %d", &l, &l2);
    char control[l], string[l2];
    scanf("%s", &*control);
    scanf("%s", &*string);

    ln = strspn(string, control);
//    int i = 0;
//    while (!ln){
//        i++;
//        ln = strspn(string + i, control);
//        if (string[i] == '\0'){
//            break;
//        }
//    }
    printf("%d", ln);

    return 0;

}
