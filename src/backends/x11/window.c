#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <X11/Xutil.h>

#include <kit/region.h>

#include "window.h"

#include <gosh/window.h>

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
    window_x11->alive = false;
    window_x11->image = NULL;

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

    /* TODO: explicitly get the proper screen or something? */
    window_x11->graphics_context = DefaultGC (backend->display, DefaultScreen (backend->display));

    /* configure the window title name */
    if (XStringListToTextProperty (&title, 1, &window_name) == 0) {

        fputs ("Failed to allocate XTextProperty for window name.", stderr);
	    exit (EXIT_FAILURE);
    }

    /* configure the icon name (name the window is iconized) */
    if (XStringListToTextProperty (&title, 1, &icon_name) == 0) {

        fputs ("Failed to allocate XTextProperty for icon name.", stderr);
	    exit (EXIT_FAILURE);
    }

    /* configure normal (size) hints */
    normal_hints.flags = 0;

    /* configure window manager hints */
    hints.flags = StateHint;
    hints.initial_state = NormalState;

    /* configure class hints */
    class_hints.res_name = title;
    class_hints.res_class = title;

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
                  StructureNotifyMask | EnterWindowMask | LeaveWindowMask   |
                  SubstructureNotifyMask);

    XMapRaised (backend->display, window_x11->window_handle);

    /* register the newly created window with the backend */
    register_window_x11 (backend, window_x11);

    /* TODO: figure out why we aren't receiving CreateNotify
     * this line is just a temporary replacement for that */
    window_x11->alive = true;

    return window_x11;
}

void destroy_window_x11_buffer (window_x11_t *window) {

    if (window->image) {

        XDestroyImage (window->image);
        window->image = NULL;
    }

    if (window->window->image.buffer) {

        destroy_buffer_without_data (window->window->image.buffer);
        window->window->image.buffer = NULL;
    }
}

void destroy_window_x11 (window_x11_t *window) {

    close_window_x11 (window);
    destroy_window_x11_buffer (window);
    free (window);
}

void close_window_x11 (window_x11_t *window) {

    if (window->alive) {

        XDestroyWindow (window->backend->display, window->window_handle);
        window->alive = false;
    }
}

void update_window_x11_region (window_x11_t *window, region_t region) {

    if (window->image == NULL || !window->alive)
        return;

    XPutImage (window->backend->display,
               window->window_handle,
               window->graphics_context,
               window->image,
               region.offset.x,
               region.offset.y,
               region.offset.x,
               region.offset.y,
               region.dimensions.x,
               region.dimensions.y);
}

void init_window_x11_buffer (window_x11_t *window, region_t region) {

    /* TODO: figure out bits per pixel and stuff??????? */

    Display *display = window->backend->display;
    /* TODO: get the proper screen? */
    int depth = DefaultDepth (display, DefaultScreen (display));

    /* free the existing image if it exists */
    if (window->image)
        destroy_window_x11_buffer (window);

    /* configure the buffer spec for the new image */
    window->window->image = make_image (PIXEL_BGRA32, NULL);
    window->window->image.buffer = create_buffer (region.dimensions, 4);

    /* create the new image matching the window's dimensions */
    window->image = XCreateImage (window->backend->display,
                                  CopyFromParent,
                                  depth,
                                  ZPixmap,
                                  0,
                                  window->window->image.buffer->data,
                                  region.dimensions.x,
                                  region.dimensions.y,
                                  32,
                                  0);
}
