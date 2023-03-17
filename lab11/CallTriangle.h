#ifndef TRIANGLE_H
#define TRIANGLE_H

struct coord{
    int x;
    int y;
};

float Perimeter(struct coord, struct coord, struct coord);

float Area(struct coord, struct coord, struct coord);

#endif