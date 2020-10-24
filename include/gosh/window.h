#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

#include "backends/x11/window.h"
#include "backend.h"
#include "event.h"
#include "buffer_spec.h"
#include "util.h"

typedef struct window_t window_t;
typedef void window_callback_t (window_t *window, event_t event, void *data);

struct window_t {

    /* the backend the window is associated with */
    backend_t *backend;

    /* the function that is called to handle window events */
    window_callback_t *callback;

    /* user data that is passed to the callback */
    void *data;

    /* the pixel buffer */
    buffer_spec_t buffer;

    /* state of the mouse and keyboard in the window */
    mouse_t mouse;
    keyboard_t keyboard;

    /* whether the window is currently mapped (on screen) */
    bool mapped;

    union {

        window_x11_t *x11;

    } windows;
};

window_t *create_window (backend_t *backend,
                         region_t region,
                         char *title,
                         window_callback_t *callback,
                         void *data);
void destroy_window (window_t *window);

/* request to close the window */
void close_window (window_t *window);

/* copy the drawing buffer to the screen */
void update_window (window_t *window);

/* copy only a part of the drawing buffer to the screen */
void update_window_region (window_t *window, region_t region);

/* send an event to a window */
void handle_event (window_t *window, event_t event);

#endif /* WINDOW_H */
