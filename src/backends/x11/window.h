#ifndef WINDOW_X11_H
#define WINDOW_X11_H

#include "backend.h"
#include "../../util.h"

struct window_t;

typedef struct window_x11_t {

    /* the x11 backend the window is associated with */
    backend_x11_t *backend;

    /* the generic window instance */
    struct window_t *window;

    /* the x11 window resource handle */
    Window window_handle;

} window_x11_t;

window_x11_t *create_window_x11 (backend_x11_t *backend,
                                 struct window_t *window,
                                 region_t region,
                                 char *title);
void destroy_window_x11 (window_x11_t *window);

#endif /* WINDOW_X11_H */
