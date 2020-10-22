#include <gosh/util.h>

bool point_equals (point_t a, point_t b) {

    return a.x == b.x && a.y == b.y;
}

bool region_equals (region_t a, region_t b) {

    return point_equals (a.offset, b.offset) &&
           point_equals (a.dimensions, b.dimensions);
}
