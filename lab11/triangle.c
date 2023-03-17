#include <math.h>
#include "CallTriangle.h"

float Perimeter(struct coord p1, struct coord p2, struct coord p3){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)) +
           sqrt(pow(p2.x - p3.x, 2) + pow(p2.y - p3.y, 2)) +
           sqrt(pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2));
}

float Area(struct coord p1, struct coord p2, struct coord p3){
    float HalfPerimeter = Perimeter(p1, p2, p3);
    return sqrt(HalfPerimeter *
                (HalfPerimeter - sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2))) *
           (HalfPerimeter - sqrt(pow(p2.x - p3.x, 2) + pow(p2.y - p3.y, 2))) *
            (HalfPerimeter - sqrt(pow(p3.x - p1.x, 2) + pow(p3.y - p1.y, 2))));
}