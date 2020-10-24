#ifndef WINDOW_X11_H
#define WINDOW_X11_H

#include <stdbool.h>

#include <X11/Xlib.h>

#include <gosh/util.h>

#include "backend.h"

struct window_t;

typedef struct window_x11_t {

    /* the x11 backend the window is associated with */
    backend_x11_t *backend;

    /* the generic window instance */
    struct window_t *window;

    /* the x11 window resource handle */
    Window window_handle;

    /* whether the window is alive on the server or not */
    bool alive;

    /* the image holding the drawing buffer */
    /* TODO: implement MIT-SHM support */
    XImage *image;

} window_x11_t;

window_x11_t *create_window_x11 (backend_x11_t *backend,
                                 struct window_t *window,
                                 region_t region,
                                 char *title);
void destroy_window_x11 (window_x11_t *window);

/* send a message to the server to close the window */
void close_window_x11 (window_x11_t *window);

/* copy a part of the drawing buffer onto the screen */
void update_window_x11_region (window_x11_t *window, region_t region);

/* initialize the drawing buffer */
void init_window_x11_buffer (window_x11_t *window, region_t region);

#endif /* WINDOW_X11_H */
