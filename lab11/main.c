#include <stdio.h>
#include "CallTriangle.h"

int main(int argc, char **argv) {

    struct coord p1;
    struct coord p2;
    struct coord p3;

    float perimeter = Perimeter(p1, p2, p3);
    float area = Area(p1, p2, p3);


    return 0;
}