#include <stdlib.h>
#include <stdio.h>

#include <X11/Xutil.h>

#include "backend.h"
#include "window.h"
#include "mouse.h"
#include "keyboard.h"

#include <gosh/window.h>
#include <gosh/event.h>



/* VBLANK SIMULATING HACK!!!!!!!!!!!!!!!!!!! 
 * TODO: GET RID OF THIS AND USE A REAL SOLUTION !!!!! AAAAAAAA */

#include <sys/time.h>
#include <time.h>

double dt = 1.0 / 60;
double last_time = 0;
double get_time () {
    struct timeval v;
    gettimeofday (&v, NULL);
    return (v.tv_usec) / 1000000.0 + v.tv_sec;
}
void sleep_seconds (double seconds) {
    struct timespec t;
    t.tv_sec = 0;
    t.tv_nsec = seconds * 1000000000;
    nanosleep (&t, NULL);
}
double until_vblank () {
    return last_time + dt - get_time();
}
bool vblank_ready () {
    return until_vblank () <= 0;
}
void wait_vblank () {
    while (!vblank_ready ())
        sleep_seconds (until_vblank ());
}
void ack_vblank (backend_x11_t *backend) {
    int i;
    event_t event;
    event.type = EVENT_VBLANK;
    last_time = get_time ();
    for (i = 0; i < backend->n_windows; i++)
        handle_event (backend->windows[i]->window, event);
}
int backend_x11_pending (backend_x11_t *backend) {
    return XPending (backend->display) + (vblank_ready () ? 1 : 0);
}

/* END: THE VBLANK SIMULATING HACK!!!!!! */



backend_x11_t *create_backend_x11 () {

    backend_x11_t *backend_x11 = malloc (sizeof (backend_x11_t));
    backend_x11->n_windows = 0;

    if (!(backend_x11->display = XOpenDisplay (NULL))) {

        fputs ("Failed to open X display.\n", stderr);
        exit (EXIT_FAILURE);
    }

    return backend_x11;
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

/* TODO: this should be the true function:
int backend_x11_pending (backend_x11_t *backend) {

    return XPending (backend->display);
}
*/

void backend_x11_process (backend_x11_t *backend) {

    char text_input[256];
    event_t window_event;
    XEvent x11_event;
    window_x11_t *window;

    /* VBLANK HACK! TODO: DO IT FOR REAL LOL */

    while (XPending (backend->display) == 0) {
        wait_vblank ();
        ack_vblank (backend);
    }
    
    if (vblank_ready ())
        ack_vblank (backend);

    /* END VBLANK HACK */

    XNextEvent (backend->display, &x11_event);
    if ((window = lookup_window_x11 (backend, x11_event.xany.window)) == NULL) {

        fputs ("Warning: could not lookup window!\n", stderr);
        return;
    }

    /* TODO: REAL vblank events per window */

    switch (x11_event.type) {

        /* when the window is created */
        case CreateNotify:

            window_event.type = EVENT_CREATE;
            window->alive = true;

            break;

        /* when the window is destroyed */
        case DestroyNotify:

            window_event.type = EVENT_DESTROY;
            window->alive = false;

            break;

        /* when the window is shown */
        case MapNotify:

            window_event.type = EVENT_SHOW;
            window->window->mapped = true;

            break;

        /* when the window is hidden */
        case UnmapNotify:

            window_event.type = EVENT_HIDE;
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
            return;
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

            /* TODO: input method support */

            /* the text input */
            if (XLookupString (&x11_event.xkey,
                               text_input,
                               sizeof (text_input),
                               NULL,
                               NULL)) {
                window_event.type        = EVENT_TEXT;
                window_event.events.text = text_input;
                handle_event (window->window, window_event);
            }

            /* the physical key event */
            window_event.type                      = EVENT_KEYBOARD;
            window_event.events.keyboard.key       = keyboard_key_x11 (x11_event.xkey.keycode);
            window_event.events.keyboard.key_state = KEYBOARD_KEY_PRESSED;

            break;

        /* when a keyboard key is released in the window */
        case KeyRelease:

            window_event.type                      = EVENT_KEYBOARD;
            window_event.events.keyboard.key       = keyboard_key_x11 (x11_event.xkey.keycode);
            window_event.events.keyboard.key_state = KEYBOARD_KEY_RELEASED;

            break;

        /* when the window is resized */
        case ConfigureNotify:

            /* TODO: if there are multiple configure notify events
             * in the queue, then should ignore all but the latest one
             * this will prevent resize-related redrawing lag */

            /* save the old region of the window */
            window_event.events.move_resize.old_region
                = window->window->region;

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
            return;
    }

    handle_event (window->window, window_event);
}
