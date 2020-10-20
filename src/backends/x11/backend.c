#include <stdlib.h>
#include <stdio.h>

#include "backend.h"
#include "window.h"
#include "../../window.h"
#include "../../event.h"

backend_x11_t *create_backend_x11 () {

    backend_x11_t *backend = malloc (sizeof (backend_x11_t));
    backend->n_windows = 0;

    if (!(backend->display = XOpenDisplay (NULL))) {

        fputs ("Failed to open X display.\n", stderr);
        exit (EXIT_FAILURE);
    }

    return backend;
}

void destroy_backend_x11 (backend_x11_t *backend) {

    XCloseDisplay (backend->display);
    free (backend);
}

void register_window_x11 (backend_x11_t *backend, window_x11_t *window) {

    backend->windows[backend->n_windows++] = window;

    /* TODO: handle this more elegantly lol */
    if (backend->n_windows == MAX_WINDOWS)
        fputs ("Warning: opened too many windows!", stderr);
}

window_x11_t *lookup_window_x11 (backend_x11_t *backend, Window window) {

    int i;
    for (i = 0; i < backend->n_windows; i++)
        if (backend->windows[i]->window_handle == window)
            return backend->windows[i];

    return NULL;
}

void backend_x11_run (backend_x11_t *backend) {

    event_t window_event;
    XEvent x11_event;
    window_x11_t *window;

    for (;;) {
        
        XNextEvent (backend->display, &x11_event);
        window = lookup_window_x11 (backend, x11_event.xany.window);
        
        switch (x11_event.type) {

            /* when the window is shown */
            case MapNotify:

                window = lookup_window_x11 (backend, x11_event.xmap.window);
                window_event.type = EVENT_MAP;

                break;

            /* when the window is hidden */
            case UnmapNotify:

                window_event.type = EVENT_UNMAP;

                break;

            /* when a region of the window needs to be redrawn */
            case Expose:

                window_event.type                              = EVENT_EXPOSE;
                window_event.events.expose_region.offset.x     = x11_event.xexpose.x;
                window_event.events.expose_region.offset.y     = x11_event.xexpose.y;
                window_event.events.expose_region.dimensions.x = x11_event.xexpose.width;
                window_event.events.expose_region.dimensions.y = x11_event.xexpose.height;

                break;

            /* when the mouse is moved in the window */
            case MotionNotify:

                window_event.type                      = EVENT_MOUSE;
                window_event.events.mouse.type         = EVENT_MOUSE_MOVE;
                window_event.events.mouse.position.x   = x11_event.xmotion.x;
                window_event.events.mouse.position.y   = x11_event.xmotion.y;

                break;

            /* when the mouse enters the window */
            case EnterNotify:

                window_event.type                      = EVENT_MOUSE;
                window_event.events.mouse.type         = EVENT_MOUSE_ENTER;
                window_event.events.mouse.position.x   = x11_event.xmotion.x;
                window_event.events.mouse.position.y   = x11_event.xmotion.y;

                break;

            /* when the mouse exits the window */
            case LeaveNotify:

                window_event.type                      = EVENT_MOUSE;
                window_event.events.mouse.type         = EVENT_MOUSE_EXIT;
                window_event.events.mouse.position.x   = x11_event.xmotion.x;
                window_event.events.mouse.position.y   = x11_event.xmotion.y;

                break;

            /* when a mouse button is pressed in the window */
            case ButtonPress:

                window_event.type                      = EVENT_MOUSE;
                window_event.events.mouse.type         = EVENT_MOUSE_BUTTON;
                window_event.events.mouse.position.x   = x11_event.xbutton.x;
                window_event.events.mouse.position.y   = x11_event.xbutton.y;
                window_event.events.mouse.button       = MOUSE_LEFT; /* TODO */
                window_event.events.mouse.button_state = MOUSE_BUTTON_PRESSED;

                break;

            /* when a mouse button is released in the window */
            case ButtonRelease:

                window_event.type                      = EVENT_MOUSE;
                window_event.events.mouse.type         = EVENT_MOUSE_BUTTON;
                window_event.events.mouse.position.x   = x11_event.xbutton.x;
                window_event.events.mouse.position.y   = x11_event.xbutton.y;
                window_event.events.mouse.button       = MOUSE_LEFT; /* TODO */
                window_event.events.mouse.button_state = MOUSE_BUTTON_RELEASED;

                break;

            /* when a keyboard key is pressed in the window */
            case KeyPress:

                window_event.type                      = EVENT_KEYBOARD;
                window_event.events.keyboard.key       = KEYBOARD_KEY_Q; /* TODO */
                window_event.events.keyboard.key_state = KEYBOARD_KEY_PRESSED;

                break;

            /* when a keyboard key is released in the window */
            case KeyRelease:

                window_event.type                      = EVENT_KEYBOARD;
                window_event.events.keyboard.key       = KEYBOARD_KEY_Q; /* TODO */
                window_event.events.keyboard.key_state = KEYBOARD_KEY_RELEASED;

                break;

            /* TODO: text input */
            /* TODO: mouse drag */

            default:
                continue;
        }

        handle_event (window->window, window_event);
    }
}
