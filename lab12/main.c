#include <stdio.h>
int main() {

    FILE * f1 = fopen("file1.txt", "r");
    FILE * f2 = fopen("file2.txt", "r");
    FILE * f3 = fopen("result.txt", "w");
    char s1[100];

    while (fscanf(f1, "%s", s1) != EOF){
        printf("%s\n", s1);
        fprintf(f3, "%s\n", s1);
    }
    while (fscanf(f2, "%s", s1) != EOF){
        printf("%s\n", s1);
        fprintf(f3, "%s\n", s1);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);

    return 0;
}
