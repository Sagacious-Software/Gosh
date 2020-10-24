#include <stdlib.h>
#include <stdio.h>

#include <gosh/backends/x11/backend.h>
#include <gosh/backends/x11/window.h>
#include <gosh/backends/x11/mouse.h>
#include <gosh/backends/x11/keyboard.h>

#include <gosh/window.h>
#include <gosh/event.h>

backend_x11_t *create_backend_x11 () {

    backend_x11_t *backend = malloc (sizeof (backend_x11_t));
    backend->running = true;
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

    while (backend->running) {
        
        XNextEvent (backend->display, &x11_event);
        window = lookup_window_x11 (backend, x11_event.xany.window);
        
        switch (x11_event.type) {

            /* when the window is created */
            case CreateNotify:

                window_event.type = EVENT_CREATE;

                break;

            /* when the window is destroyed */
            case DestroyNotify:

                window_event.type = EVENT_DESTROY;

                break;

            /* when the window is shown */
            case MapNotify:

                window_event.type = EVENT_MAP;
                window->window->mapped = true;

                break;

            /* when the window is hidden */
            case UnmapNotify:

                window_event.type = EVENT_UNMAP;
                window->window->mapped = false;

                break;

            /* when a region of the window needs to be redrawn */
            case Expose: {

                /* get the region that was exposed */
                region_t region;
                region.offset.x     = x11_event.xexpose.x;
                region.offset.y     = x11_event.xexpose.y;
                region.dimensions.x = x11_event.xexpose.width;
                region.dimensions.y = x11_event.xexpose.height;

                /* redraw the exposed region */
                update_window_x11_region (window, region);

                /* there isn't a user-facing event for this */
                continue;
            }

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
                window_event.events.mouse.button       = mouse_button_x11 (x11_event.xbutton.button);
                window_event.events.mouse.button_state = MOUSE_BUTTON_PRESSED;

                break;

            /* when a mouse button is released in the window */
            case ButtonRelease:

                window_event.type                      = EVENT_MOUSE;
                window_event.events.mouse.type         = EVENT_MOUSE_BUTTON;
                window_event.events.mouse.position.x   = x11_event.xbutton.x;
                window_event.events.mouse.position.y   = x11_event.xbutton.y;
                window_event.events.mouse.button       = mouse_button_x11 (x11_event.xbutton.button);
                window_event.events.mouse.button_state = MOUSE_BUTTON_RELEASED;

                break;

            /* when a keyboard key is pressed in the window */
            case KeyPress:

                window_event.type                      = EVENT_KEYBOARD;
                /* TODO: determine whether to include character keysym here too */
                window_event.events.keyboard.key       = keyboard_key_x11 (x11_event.xkey.keycode);
                window_event.events.keyboard.key_state = KEYBOARD_KEY_PRESSED;

                break;

            /* when a keyboard key is released in the window */
            case KeyRelease:

                window_event.type                      = EVENT_KEYBOARD;
                window_event.events.keyboard.key       = keyboard_key_x11 (x11_event.xkey.keycode);
                window_event.events.keyboard.key_state = KEYBOARD_KEY_RELEASED;

                break;

            /* TODO: text input */
            /* TODO: mouse drag */

            /* when the window is resized */
            case ConfigureNotify:

                /* save the old region of the window */
                window_event.events.move_resize.old_region
                    = window->window->buffer.region;

                /* get the new region of the window */
                window_event.events.move_resize.new_region.offset.x
                    = x11_event.xconfigure.x;
                window_event.events.move_resize.new_region.offset.y
                    = x11_event.xconfigure.y;
                window_event.events.move_resize.new_region.dimensions.x
                    = x11_event.xconfigure.width;
                window_event.events.move_resize.new_region.dimensions.y
                    = x11_event.xconfigure.height;

                /* reinitialize the pixel buffer for the new size */
                init_window_x11_buffer (window,
                                        window_event.events.move_resize.new_region);

                /* if the window size has changed,
                 * treat this as a resize event rather than a move event */
                window_event.type
                    = point_equals (window_event.events.move_resize.new_region.dimensions,
                                    window_event.events.move_resize.old_region.dimensions)
                    ? EVENT_MOVE : EVENT_RESIZE;

                break;

            default:
                continue;
        }

        handle_event (window->window, window_event);
    }
}

void backend_x11_exit (backend_x11_t *backend) {

    backend->running = false;
}
