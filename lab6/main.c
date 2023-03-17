#include <stdio.h>
#include <malloc.h>

int main() {
    // Task 1 init array with pointer
    int array[4];
    int* arr = &array[0];
    // inserting values
    arr[0] = 1000, arr[1] = 1001, arr[2] = 1002, arr[3] = 1003;

    // printing array with pointer
    printf("Task 1\n");
    for (int i=0; i < 4; i++){
        printf("%d\n", *(array + i));
    }

    // Task 2 init array2
    int* arr2 = (int*) calloc (4, sizeof(int));
    // inserting values
    arr2[0] = 1000, arr2[1] = 1001, arr2[2] = 1002, arr2[3] = 1003;

    // printing values with pointer
    printf("\nTask 2\n");
    for (int i=0; i < 4; i++){
        printf("%d\n", *(arr2 + i));
    }
    // free the memory
    free(arr2);
    return 0;
}
