#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

#ifdef ENABLE_BACKEND_X11
#include "backends/x11/window.h"
#endif

#ifdef ENABLE_BACKEND_WINDOWS
#include "backends/windows/window.h"
#endif

#include "backend.h"
#include "event.h"
#include "util.h"

typedef struct window_t window_t;
typedef void window_callback_t (window_t *window, event_t event, void *data);

struct window_t {

    /* the backend the window is associated with */
    backend_t *backend;

    /* the function that is called to handle window events
     * this can be null if this is not needed */
    window_callback_t *callback;

    /* user data that is passed to the callback */
    void *data;

    /* the position and size of the buffer on screen */
    region_t region;

    /* the pixel format */
    size_t bytes_per_pixel;

    /* the raw pixel data */
    void *pixels;

    /* whether the window is currently mapped (on screen) */
    bool mapped;

    /* state of the mouse and keyboard in the window */
    mouse_t mouse;
    keyboard_t keyboard;

    union {

#ifdef ENABLE_BACKEND_X11
        window_x11_t *x11;
#endif
#ifdef ENABLE_BACKEND_WINDOWS
        window_windows_t *windows;
#endif

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

/* get the size of the pixel buffer in bytes */
int window_buffer_size (window_t *window);

/* get the memory location of a pixel in a pixel buffer */
void *pixel_address (window_t *window, point_t position);

/* set the value of a pixel to a given rgba color */
void set_pixel (window_t *window, point_t position, rgba_color_t color);

/* retrieve the value of a pixel */
rgba_color_t get_pixel (window_t *window, point_t position);

/* allocate new memory for a pixel value and fill it with binary packed color data */
void *pack_color (window_t *window, rgba_color_t color);

/* unpack binary packed color data */
rgba_color_t unpack_color (window_t *window, void *packed_color);

#endif /* WINDOW_H */
