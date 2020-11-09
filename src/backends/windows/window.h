#ifndef WINDOW_WINDOWS_H
#define WINDOW_WINDOWS_H

#include <windows.h>

#include <stdbool.h>

#include <gosh/event.h>

#include "backend.h"

#define EVENT_QUEUE_SIZE 256

struct window_t;

typedef struct window_windows_t {

    /* the windows backend the window is associated with */
    backend_windows_t *backend;

    /* the generic window instance */
    struct window_t *window;

    /* the windows window handle */
    HWND handle;

    /* obligatory event queue bc windows api is not very nice */
    event_t queue[EVENT_QUEUE_SIZE];
    size_t i_event_read;
    size_t i_event_write;

} window_windows_t;

window_windows_t *create_window_windows (backend_windows_t *backend,
                                         struct window_t *window,
                                         region_t region,
                                         char *title);
void destroy_window_windows (window_windows_t *window);

/* send a message to the server to close the window */
void close_window_windows (window_windows_t *window);

/* queue an event */
void queue_event_window_windows (window_windows_t *window, event_t event);

/* get next event on the queue or return NULL if empty */
event_t *get_event_window_windows (window_windows_t *window);

/* copy a part of the drawing buffer onto the screen */
void update_window_windows_region (window_windows_t *window, region_t region);

/* initialize the drawing buffer */
void init_window_windows_buffer (window_windows_t *window, region_t region);

#endif /* WINDOW_WINDOWS_H */
