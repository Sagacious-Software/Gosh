#ifndef BACKEND_WINDOWS_H
#define BACKEND_WINDOWS_H

#include <windows.h>

#include <gosh/util.h>

#define MAX_WINDOWS 256

/* the name of the windows wind wclass to be registered */
extern const char WINDOW_CLASS_NAME[];

struct window_windows_t;

typedef struct backend_windows_t {

    /* windows application instance handle */
    HINSTANCE handle;

    /* windows opened */
    struct window_windows_t *windows[MAX_WINDOWS];
    size_t n_windows;

} backend_windows_t;

backend_windows_t *create_backend_windows ();
void destroy_backend_windows (backend_windows_t *backend);

void register_window_windows (backend_windows_t *backend, struct window_windows_t *window);

int backend_windows_pending (backend_windows_t *backend);
void backend_windows_process (backend_windows_t *backend);
void backend_windows_exit (backend_windows_t *backend);

#endif /* BACKEND_WINDOWS_H */
