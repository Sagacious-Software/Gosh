#ifndef WINDOW_WINDOWS_H
#define WINDOW_WINDOWS_H

#include <stdbool.h>

#include <windows.h>

#include <gosh/util.h>

#include "backend.h"

struct window_t;

typedef struct window_windows_t {

    /* the windows backend the window is associated with */
    backend_windows_t *backend;

    /* the generic window instance */
    struct window_t *window;

    /* the windows window handle */
    HWND handle;

} window_windows_t;

window_windows_t *create_window_windows (backend_windows_t *backend,
                                         struct window_t *window,
                                         region_t region,
                                         char *title);
void destroy_window_windows (window_windows_t *window);

/* send a message to the server to close the window */
void close_window_windows (window_windows_t *window);

/* copy a part of the drawing buffer onto the screen */
void update_window_windows_region (window_windows_t *window, region_t region);

/* initialize the drawing buffer */
void init_window_windows_buffer (window_windows_t *window, region_t region);

/* allocate new memory for a pixel value and fill it with binary packed color data */
void *pack_color_windows (window_windows_t *window, rgba_color_t color);

/* unpack binary packed color data */
rgba_color_t unpack_color_windows (window_windows_t *window, void *packed_color);

#endif /* WINDOW_WINDOWS_H */
