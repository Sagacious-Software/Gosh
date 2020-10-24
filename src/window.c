#include <stdlib.h>
#include <string.h>

#include <gosh/window.h>

window_t *create_window (backend_t *backend,
                         region_t region,
                         char *title,
                         window_callback_t *callback,
                         void *data) {

    window_t *window = malloc (sizeof (window_t));
    memset (window, 0, sizeof (window_t));
    window->backend = backend;
    window->callback = callback;
    window->data = data;

    switch (backend->type) {

        case BACKEND_X11:
            window->windows.x11 = create_window_x11 (backend->backends.x11,
                                                     window,
                                                     region,
                                                     title);
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

void close_window (window_t *window) {

    switch (window->backend->type) {

        case BACKEND_X11:
            close_window_x11 (window->windows.x11);
            break;

        default:
            break;
    }
}

void update_window (window_t *window) {

    region_t region;
    region.offset.x = 0;
    region.offset.y = 0;
    region.dimensions.x = window->buffer.region.dimensions.x;
    region.dimensions.y = window->buffer.region.dimensions.y;
    update_window_region (window, region);
}

void update_window_region (window_t *window, region_t region) {

    switch (window->backend->type) {

        case BACKEND_X11:
            update_window_x11_region (window->windows.x11, region);
            break;

        default:
            break;
    }
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
    window->callback (window, event, window->data);
}
