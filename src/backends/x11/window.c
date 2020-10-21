#include <stdlib.h>
#include <stdio.h>

#include <X11/Xutil.h>

#include "window.h"
#include "../../window.h"

window_x11_t *create_window_x11 (backend_x11_t *backend,
                                 window_t *window,
                                 region_t region,
                                 char *title) {

    XSetWindowAttributes attributes;

    XSizeHints normal_hints;
    XWMHints hints;
    XClassHint class_hints;

    XTextProperty window_name, icon_name;

    window_x11_t *window_x11 = malloc (sizeof (window_x11_t));
    window_x11->backend = backend;
    window_x11->window = window;

    window_x11->window_handle = XCreateWindow (backend->display,
                                               DefaultRootWindow (backend->display),
                                               region.offset.x,
                                               region.offset.y, 
                                               region.dimensions.x,
                                               region.dimensions.y,
                                               0,
                                               CopyFromParent,
                                               CopyFromParent,
                                               CopyFromParent,
                                               0,
                                               &attributes);

    /* configure the window title name */
    if (XStringListToTextProperty (&title, 1, &window_name) == 0) {

        fputs ("Failed to allocate XTextProperty for window name.", stderr);
	    exit (EXIT_FAILURE);
    }

    /* configure the window icon name (name when it's iconized) */
    if (XStringListToTextProperty (&title, 1, &icon_name) == 0) {

        fputs ("Failed to allocate XTextProperty for window name.", stderr);
	    exit (EXIT_FAILURE);
    }

    /* configure normal (size) hints */
    normal_hints.flags = 0;

    /* configure window manager hints */
    hints.flags = StateHint;
    hints.initial_state = NormalState;

    /* configure class hints */
    class_hints.res_name = "Gosh Application";
    class_hints.res_class = "gosh_application";

    XSetWMProperties (backend->display,
                      window_x11->window_handle,
                      &window_name,
                      &icon_name,
                      NULL, 0,
                      &normal_hints,
                      &hints,
                      &class_hints);

    XSelectInput (backend->display, window_x11->window_handle,
                  ExposureMask        | ButtonPressMask | ButtonReleaseMask |
                  PointerMotionMask   | KeyPressMask    | KeyReleaseMask    |
                  StructureNotifyMask | EnterWindowMask | LeaveWindowMask);

    XMapRaised (backend->display, window_x11->window_handle);

    /* register the newly created window with the backend */
    register_window_x11 (backend, window_x11);

    return window_x11;
}

void destroy_window_x11 (window_x11_t *window) {

    XDestroyWindow (window->backend->display, window->window_handle);
    free (window);
}
