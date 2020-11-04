#ifndef WINDOW_H
#define WINDOW_H

#include <kit/region.h>
#include <kit/image.h>

#include <stdbool.h>

#include "backend.h"
#include "event.h"

typedef struct window_t window_t;
typedef void window_callback_t (window_t *window, event_t event, void *data);

struct window_t {

    /* the backend the window is associated with */
    backend_t *backend;

    /* the backend specific window instance */
    void *window;

    /* the function that is called to handle window events
     * this can be null if this is not needed */
    window_callback_t *callback;

    /* user data that is passed to the callback */
    void *data;

    /* the position and size of the buffer on screen */
    region_t region;

    /* the image to paint into the pixel buffer */
    image_t image;

    /* whether the window is currently mapped (on screen) */
    bool mapped;

    /* state of the mouse and keyboard in the window */
    mouse_t mouse;
    keyboard_t keyboard;
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

/* set the value of a pixel to a given rgb color */
void set_pixel (window_t *window, vec2_t position, color_t color);

/* retrieve the value of a pixel */
color_t get_pixel (window_t *window, vec2_t position);

#endif /* WINDOW_H */
