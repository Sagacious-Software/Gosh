#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <gosh/window.h>

#ifdef ENABLE_BACKEND_X11
#include "backends/x11/window.h"
#endif

#ifdef ENABLE_BACKEND_WINDOWS
#include "backends/windows/window.h"
#endif

window_t *create_window (backend_t *backend,
                         region_t region,
                         char *title,
                         window_callback_t *callback,
                         void *data) {

    window_t *window = malloc (sizeof (window_t));
    memset (window, 0, sizeof (window_t));
    window->backend = backend;
    window->callback = callback;
    window->data = data;

    switch (backend->type) {

#ifdef ENABLE_BACKEND_X11
        case BACKEND_X11:
            window->windows.x11 = create_window_x11 (backend->backend,
                                                     window,
                                                     region,
                                                     title);
            break;

#endif
#ifdef ENABLE_BACKEND_WINDOWS
        case BACKEND_WINDOWS:
            window->windows.windows = create_window_windows (backend->backend,
                                                             window,
                                                             region,
                                                             title);
            break;

#endif
        default:
            break;
    }

    return window;
}

void destroy_window (window_t *window) {

    switch (window->backend->type) {

#ifdef ENABLE_BACKEND_X11
        case BACKEND_X11:
            destroy_window_x11 (window->window);
            break;

#endif
#ifdef ENABLE_BACKEND_WINDOWS
        case BACKEND_WINDOWS:
            destroy_window_windows (window->window);
            break;

#endif
        default:
            break;
    }

    free (window);
}

void close_window (window_t *window) {

    switch (window->backend->type) {

#ifdef ENABLE_BACKEND_X11
        case BACKEND_X11:
            close_window_x11 (window->window);
            break;

#endif
#ifdef ENABLE_BACKEND_WINDOWS
        case BACKEND_WINDOWS:
            close_window_windows (window->window);
            break;

#endif
        default:
            break;
    }
}

void update_window (window_t *window) {

    /* TODO: go through all the code and replace instances
     * of manually creating points, regions, and colors,
     * with the constructor functions for each */
    region_t region;
    region.offset.x = 0;
    region.offset.y = 0;
    region.dimensions.x = window->region.dimensions.x;
    region.dimensions.y = window->region.dimensions.y;
    update_window_region (window, region);
}

void update_window_region (window_t *window, region_t region) {

    switch (window->backend->type) {

#ifdef ENABLE_BACKEND_X11
        case BACKEND_X11:
            update_window_x11_region (window->window, region);
            break;

#endif
#ifdef ENABLE_BACKEND_WINDOWS
        case BACKEND_WINDOWS:
            update_window_windows_region (window->window, region);
            break;

#endif
        default:
            break;
    }
}

void handle_event (window_t *window, event_t event) {

    if (window->callback == NULL)
        return;

    /* keep track of the mouse and keyboard state */
    switch (event.type) {

        /* keep track of the mouse state */
        case EVENT_MOUSE:

            /* keep track of the mouse position */
            window->mouse.position = event.events.mouse.position;

            /* keep track of the mouse button state */
            if (event.events.mouse.type == EVENT_MOUSE_BUTTON)
                window->mouse.buttons[event.events.mouse.button]
                    = event.events.mouse.button_state;

            break;

        /* keep track of the keyboard state */
        case EVENT_KEYBOARD:
            window->keyboard.keys[event.events.keyboard.key]
                = event.events.keyboard.key_state;
            break;

        default:
            break;
    }

    /* send the event to the window's assigned event handler callback */
    window->callback (window, event, window->data);
}

int window_buffer_size (window_t *window) {

    return window->bytes_per_pixel *
           window->region.dimensions.x *
           window->region.dimensions.y;
}

void *pixel_address (window_t *window, point_t position) {

    size_t index = position.x + position.y * window->region.dimensions.x;
    size_t offset = index * window->bytes_per_pixel;
    return (void *) ((uint8_t *) window->pixels + offset);
}

void set_pixel (window_t *window, point_t position, rgba_color_t color) {

    void *packed_color = pack_color (window, color);
    memcpy (pixel_address (window, position),
            packed_color,
            window->bytes_per_pixel);
    free (packed_color);
}

rgba_color_t get_pixel (window_t *window, point_t position) {

    return unpack_color (window, pixel_address (window, position));
}

void *pack_color (window_t *window, rgba_color_t color) {

    switch (window->backend->type) {

#ifdef ENABLE_BACKEND_X11
        case BACKEND_X11:
            return pack_color_x11 (window->window, color);

#endif
#ifdef ENABLE_BACKEND_WINDOWS
        case BACKEND_WINDOWS:
            return pack_color_windows (window->window, color);

#endif
        default:
            return NULL;
    }
}

rgba_color_t unpack_color (window_t *window, void *packed_color) {

    switch (window->backend->type) {

#ifdef ENABLE_BACKEND_X11
        case BACKEND_X11:
            return unpack_color_x11 (window->window, packed_color);

#endif
#ifdef ENABLE_BACKEND_WINDOWS
        case BACKEND_WINDOWS:
            return unpack_color_windows (window->window, packed_color);

#endif
        default:
            return NULL_COLOR;
    }
}
