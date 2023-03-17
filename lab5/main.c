#include <stdio.h>

int main() {
    // initializing
    int arr[] = {77, 12, 74, 34, 56, 78, 234, 678};
    // printing array
    for (int i=0; i < 8; i++){
        printf("%d ", arr[i]);
    }
    //going to next line
    printf("\n");

    // init matrix
    int matrix1[2][2] = {{1, 0}, {1, 4}};
    int matrix2[2][2] = {{1, 2}, {0, 1}};
    // operate matrix
    int matrixRes[2][2];

    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matrixRes[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                matrixRes[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    // printing matrix in a table
    for (int a=0; a < 2; a++){
        for (int b=0; b < 2; b++){
            printf("%d\n", matrixRes[a][b]);
        }
    }
    return 0;
}
