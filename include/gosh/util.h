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

typedef struct rgba_color_t {

    double red;
    double green;
    double blue;
    double alpha;

} rgba_color_t;

#define NULL_COLOR (make_color (0, 0, 0, 0))

point_t make_point (int x, int y);
region_t make_region (int x, int y, int width, int height);
region_t make_region_bounds (int left, int top, int right, int bottom);
rgba_color_t make_color (double red, double green, double blue, double alpha);

bool point_equals (point_t a, point_t b);
bool region_equals (region_t a, region_t b);

rgba_color_t multiply_colors (rgba_color_t a, rgba_color_t b);

typedef void idle_callback_t (void *data);

#endif /* UTIL_H */
