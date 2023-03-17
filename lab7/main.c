#include <stdio.h>

// Task 1 enum of lamps
enum Lamps{
    incandescent,
    daylight,
    halogen,
    energySaving
};

// Task 2 rectangular struct
struct Rectangular{
    int x;
    int y;
    int a;
    int b;
    int area;
};

// Task 2 count rectangular area
int countArea(int a, int b){
    return a * b;
}

// Task 3 bit-field MP3Player
union {
    int p;
    struct{
        int play: 1;
        int pause: 1;
        int record: 1;
    };
}mp;

int main() {
    // Task 1
    enum Lamps hl; // using enum
    hl = halogen;
    printf("Task 1: %d\n", hl);

    // Task 2
    struct Rectangular rectangular;
    rectangular.x = 9;
    rectangular.y = 18;
    rectangular.a = 11;
    rectangular.b = 6;
    rectangular.area = countArea(rectangular.a, rectangular.b);
    printf("Task 2: %d\n", rectangular.area);

    // Task 3
    printf("Task 3:");
    int n;
    scanf("%x", &n);

    mp.p = n;
    printf("%d %d %d\n", mp.play * -1, mp.pause * -1, mp.record * -1);

    return 0;
}
