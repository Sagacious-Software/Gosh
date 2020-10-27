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
                                                  NULL)) == NULL)
        error_windows ("Gosh Error", "Failed to create Windows window.");

    ShowWindow (window_windows->handle, SW_SHOWNORMAL);
    UpdateWindow (window_windows->handle);

    /* TODO: put this some where better */
    window->region = region;
    window->bytes_per_pixel = 4;
    window->pixels
        = malloc (region.dimensions.x * region.dimensions.y * 4);

    return window_windows;
}

void destroy_window_windows (window_windows_t *window) {

    free (window->window->pixels);

    PostQuitMessage (0);

    close_window_windows (window);
    free (window);
}

void close_window_windows (window_windows_t *window) {

    DestroyWindow (window->handle);
}

void update_window_windows_region (window_windows_t *window, region_t region) {

    /* TODO */
}

void *pack_color_windows (window_windows_t *window, rgba_color_t color) {

    /* TODO: make this actually generic */

    uint8_t *pixel;
    uint8_t red, green, blue, alpha;

    red   = color.red   * 255;
    green = color.green * 255;
    blue  = color.blue  * 255;
    alpha = color.alpha * 255;

    pixel = malloc (4);
    pixel[0] = blue;
    pixel[1] = green;
    pixel[2] = red;
    pixel[3] = alpha;

    return (void *) pixel;
}

rgba_color_t unpack_color_windows (window_windows_t *window, void *packed_color) {

    uint8_t *pixel;
    rgba_color_t color;

    pixel = (uint8_t *) packed_color;
    color.blue  = pixel[0] / 255.0;
    color.green = pixel[1] / 255.0;
    color.red   = pixel[2] / 255.0;
    color.alpha = pixel[3] / 255.0;

    return color;
}
