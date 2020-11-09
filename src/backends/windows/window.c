#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "window.h"
#include "util.h"

#include <gosh/window.h>

window_windows_t *create_window_windows (backend_windows_t *backend,
                                         window_t *window,
                                         region_t region,
                                         char *title) {

    window_windows_t *window_windows = malloc (sizeof (window_windows_t));
    window_windows->backend = backend;
    window_windows->window = window;
    window_windows->i_event_read = 0;
    window_windows->i_event_write = 0;

    if ((window_windows->handle = CreateWindowEx (WS_EX_CLIENTEDGE,
                                                  WINDOW_CLASS_NAME,
                                                  title,
                                                  WS_OVERLAPPEDWINDOW, /* TODO: investigate */
                                                  region.offset.x     ? region.offset.x     : CW_USEDEFAULT,
                                                  region.offset.y     ? region.offset.y     : CW_USEDEFAULT,
                                                  region.dimensions.x ? region.dimensions.x : CW_USEDEFAULT,
                                                  region.dimensions.y ? region.dimensions.y : CW_USEDEFAULT,
                                                  NULL,
                                                  NULL,
                                                  backend->handle,
                                                  window_windows)) == NULL)
        error_windows ("Gosh Error", "Failed to create Windows window.");

    ShowWindow (window_windows->handle, SW_SHOWNORMAL);
    UpdateWindow (window_windows->handle);

    /* register the newly created window with the backend */
    register_window_windows (backend, window_windows);

    /* TODO: figure out if this needs to be here */
    init_window_windows_buffer (window_windows, region);

    return window_windows;
}

void destroy_window_windows (window_windows_t *window) {

    destroy_buffer (window->window->image.buffer);

    PostQuitMessage (0);

    close_window_windows (window);
    free (window);
}

void close_window_windows (window_windows_t *window) {

    DestroyWindow (window->handle);
}

void queue_event_window_windows (window_windows_t *window, event_t event) {

    window->queue[window->i_event_write++] = event;
    window->i_event_write %= EVENT_QUEUE_SIZE;
}

event_t *get_event_window_windows (window_windows_t *window) {

    event_t *event;

    if (window->i_event_read == window->i_event_write)
        return NULL;

    event = &window->queue[window->i_event_read++];
    window->i_event_read %= EVENT_QUEUE_SIZE;

    return event;
}

void update_window_windows_region (window_windows_t *window, region_t region) {

    /* TODO: pick a specific region */
    InvalidateRect (window->handle, NULL, false);
}

void init_window_windows_buffer (window_windows_t *window, region_t region) {

    /* TODO: fifgure out best way to do this ; and do it Right , silly */
    if (window->window->image.buffer)
        destroy_buffer (window->window->image.buffer);

    window->window->image = make_image (PIXEL_RGBA32, NULL);
    window->window->image.buffer = create_buffer (region.dimensions, 4);
}
