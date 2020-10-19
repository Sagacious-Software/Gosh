#ifndef WINDOW_H
#define WINDOW_H

#include "backend.h"
#include "buffer.h"
#include "event.h"

typedef struct window_t window_t;
typedef void window_callback_t (window_t *window, event_t event);

struct window_t {

    /* the backend the window is associated with */
    backend_t *backend;

    /* TODO: actually not gonna store a buffer at all, it will be IMILICT & PASSED */
    buffer_t *buffer;

    /* the function that is called to handle window events */
    window_callback_t *callback;

    /* state of the mouse and keyboard in the window */
    mouse_t mouse;
    keyboard_t keyboard;

};

window_t *create_window (backend_t *backend, window_callback_t *callback);
window_t *destroy_window (window_t *window);

#endif /* WINDOW_H */
