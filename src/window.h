#ifndef WINDOW_H
#define WINDOW_H

#include "backends/x11/window.h"
#include "backend.h"
#include "buffer.h"
#include "event.h"
#include "util.h"

typedef struct window_t window_t;
typedef void window_callback_t (window_t *window, event_t event);

struct window_t {

    /* the backend the window is associated with */
    backend_t *backend;

    /* the function that is called to handle window events */
    window_callback_t *callback;

    /* state of the mouse and keyboard in the window */
    mouse_t mouse;
    keyboard_t keyboard;

    union {

        window_x11_t *x11;

    } windows;
};

window_t *create_window (backend_t *backend,
                         window_callback_t *callback,
                         region_t region,
                         char *title);
void destroy_window (window_t *window);

void handle_event (window_t *window, event_t event);

#endif /* WINDOW_H */
