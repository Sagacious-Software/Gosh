#include <stdlib.h>

#include "window.h"
#include "../../window.h"

window_x11_t *create_window_x11 (backend_x11_t *backend, window_t *window) {

    window_x11_t *window_x11 = malloc (sizeof (window_x11_t));
    window_x11->backend = backend;
    window_x11->window = window;

    /* TODO: use the other method */
    window_x11->window_handle = XCreateSimpleWindow (backend->display,
                                                     DefaultRootWindow (backend->display),
                                                     0, 0,	200, 300, 5, 0, 0);

    XSelectInput (backend->display, window_x11->window_handle,
                  ExposureMask      | ButtonPressMask | ButtonReleaseMask |
                  PointerMotionMask | KeyPressMask    | KeyReleaseMask);

    XMapRaised (backend->display, window_x11->window_handle);

    /* register the newly created window with the backend */
    register_window_x11 (backend, window_x11);

    return window_x11;
}

void destroy_window_x11 (window_x11_t *window) {

    XDestroyWindow (window->backend->display, window->window_handle);
    free (window);
}
