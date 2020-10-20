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

    /* keep track of the mouse and keyboard state */
    switch (event.type) {

        /* keep track of the mouse state */
        case EVENT_MOUSE:

            /* keep track of the mouse position */
            window->mouse.position = event.events.mouse.position;

            /* keep track of the mouse button state */
            if (event.events.mouse.type == EVENT_MOUSE_BUTTON)
                window->mouse.buttons[event.events.mouse.button]
                    = event.events.mouse.button_state;

            break;

        /* keep track of the keyboard state */
        case EVENT_KEYBOARD:
            window->keyboard.keys[event.events.keyboard.key]
                = event.events.keyboard.key_state;
            break;

        default:
            break;
    }

    /* send the event to the window's assigned event handler callback */
    window->callback (window, event);
}
