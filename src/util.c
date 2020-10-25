#include <gosh/util.h>

point_t make_point (int x, int y) {

    point_t point;
    point.x = x;
    point.y = y;
    return point;
}

region_t make_region (int x, int y, int width, int height) {

    region_t region;
    region.offset.x     = x;
    region.offset.y     = y;
    region.dimensions.x = width;
    region.dimensions.y = height;
    return region;
}

rgba_color_t make_color (double red, double green, double blue, double alpha) {

    rgba_color_t color;
    color.red = red;
    color.green = green;
    color.blue = blue;
    color.alpha = alpha;
    return color;
}

bool point_equals (point_t a, point_t b) {

    return a.x == b.x && a.y == b.y;
}

bool region_equals (region_t a, region_t b) {

    return point_equals (a.offset, b.offset) &&
           point_equals (a.dimensions, b.dimensions);
}

rgba_color_t multiply_colors (rgba_color_t a, rgba_color_t b) {

    return make_color (a.red   * b.red,
                       a.green * b.green,
                       a.blue  * b.blue,
                       a.alpha * b.alpha);
}
