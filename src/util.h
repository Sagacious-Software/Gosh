#ifndef UTIL_H
#define UTIL_H

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

#endif /* UTIL_H */
