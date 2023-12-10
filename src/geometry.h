#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "types.h"
#include <gint/std/stdlib.h>

typedef struct {
    i16 x, y;
} Point;
Point new_point(u16 x, u16 y) {
    Point tmp;
    
    tmp.x = x;
    tmp.y = y;

    return tmp;
}

typedef struct {
    i16 x1, y1, x2, y2;
} Line;
Line new_line(i16 x1, i16 y1, i16 x2, i16 y2) {
    Line tmp;
    
    tmp.x1 = x1;
    tmp.y1 = y1;
    tmp.x2 = x2;
    tmp.y2 = y2;

    return tmp;
}

Line new_line_from_points(Point v1, Point v2) {
    return new_line(v1.x, v1.y, v2.x, v2.y);
}

Line new_vert_line(i16 x, i16 y1, i16 y2) {
    return new_line(x, y1, x, y2);
}

#endif /* GEOMETRY_H */