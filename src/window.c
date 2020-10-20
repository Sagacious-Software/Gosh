#include <stdlib.h>

#include "window.h"

window_t *create_window (backend_t *backend, window_callback_t *callback) {

    window_t *window = malloc (sizeof (window_t));
    window->backend = backend;
    window->callback = callback;

    /* TODO: init mouse and keyboard state */

    switch (backend->type) {

        case BACKEND_X11:
            window->windows.x11 = create_window_x11 (backend->backends.x11, window);
            break;

        default:
            break;
    }

    return window;
}

void destroy_window (window_t *window) {

    switch (window->backend->type) {

        case BACKEND_X11:
            destroy_window_x11 (window->windows.x11);
            break;

        default:
            break;
    }

    free (window);
}

void handle_event (window_t *window, event_t event) {

    /* TODO: update mouse and keyboard state */

    window->callback (window, event);
}
