#ifndef BACKEND_X11_H
#define BACKEND_X11_H

#include <X11/Xlib.h>

#define MAX_WINDOWS 256

struct window_x11_t;

typedef struct backend_x11_t {

    /* the connection to the X server */
    Display *display;

    /* windows opened on the server */
    struct window_x11_t *windows[MAX_WINDOWS];
    size_t n_windows;

} backend_x11_t;

backend_x11_t *create_backend_x11 ();
void destroy_backend_x11 (backend_x11_t *backend);

void register_window_x11 (backend_x11_t *backend, struct window_x11_t *window);

int backend_x11_pending (backend_x11_t *backend);
void backend_x11_process (backend_x11_t *backend);
void backend_x11_exit (backend_x11_t *backend);

#endif /* BACKEND_X11_H */
