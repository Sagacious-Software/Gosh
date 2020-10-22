#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

typedef struct point_t {

    int x;
    int y;

} point_t;

typedef struct region_t {

    /* position from the top left corner */
    point_t offset;

    /* width and height of the region */
    point_t dimensions;

} region_t;

bool point_equals (point_t a, point_t b);
bool region_equals (region_t a, region_t b);

#endif /* UTIL_H */
