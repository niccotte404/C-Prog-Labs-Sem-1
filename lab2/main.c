#include <stdio.h>
#include <math.h> // use lib math 'cause of sqrt

int main() {
    //initializing && scanning var
    double a;
    scanf("%lf", &a);

    // solving the functions
    double z1 = ((a+2)/sqrt(a*2e0) - a/(sqrt(a*2e0) + 2) + 2/(a - sqrt(a*2e0))) * ((sqrt(a) - sqrt(2e0)) / (a + 2e0));
    double z2 = 1 / (sqrt(a) + sqrt(2e0));
    printf("z1: %lf\n", z1);
    printf("z2: %lf", z2);
    return 0;
}
