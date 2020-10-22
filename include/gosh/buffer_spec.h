#ifndef BUFFER_SPEC_H
#define BUFFER_SPEC_H

#include "util.h"

typedef struct buffer_spec_t {

    /* the position and size of the buffer on screen */
    region_t region;

    /* the pixel format */
    /* TODO */

    /* the raw pixel data */
    void *pixels;

} buffer_spec_t;

#endif /* BUFFER_SPEC_H */
