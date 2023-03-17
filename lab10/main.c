#include <stdio.h>
#include <stdlib.h>

void CreateArray(int * arr, int n){
    int i = 0;
    while (n > 0){
        arr[i] = n % 10;
        printf("%d ", arr[i]);
        n /= 10;
        i++;
    }
    printf("\n");
}

void DeleteSpaces(char * str, char * strcopy, int i, int j, int k1){
    if (str[i] == '\0'){
        return;
    }
    if ((str[i-1] == ' ' && str[i] == ' ') || (str[i-1] == '(' && str[i] == ' ') ||
    (str[i-1] == '{' && str[i] == ' ') || (str[i-1] == '[' && str[i] == ' ')){
        i++;
    }
    else{
        strcopy[j] = str[i];
        j++;
        i++;
    }
    DeleteSpaces(str, strcopy, i, j, k1);
}

int main() {

    // Task 3
    int n;
    int * arr = malloc (11 * sizeof(int)); // max int = +-2147483647
    printf("Task 3:\n");
    scanf("%d", &n);
    CreateArray(arr, n);

    // Task 5
    printf("Task 5:\n");
    char *s = calloc(256, sizeof (char));
    char *scpy = calloc(256, sizeof (char));
    fflush(stdin); // отчистка буффера
    gets(s);
    DeleteSpaces(s, scpy, 0, 0, 0);
    printf("%s", scpy);

    return 0;
}
