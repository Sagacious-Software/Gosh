#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>

#ifdef ENABLE_BACKEND_X11
#include "backends/x11/backend.h"
#endif

#ifdef ENABLE_BACKEND_WINDOWS
#include "backends/windows/backend.h"
#endif

typedef enum backend_type_t {

    BACKEND_AUTO,
#ifdef ENABLE_BACKEND_X11
    BACKEND_X11,
#endif
#ifdef ENABLE_BACKEND_WINDOWS
    BACKEND_WINDOWS,
#endif

    NUM_BACKEND_TYPE

} backend_type_t;

typedef struct backend_t {

    /* the type of the backend */
    backend_type_t type;

    /* whether the backend is currenly running */
    bool running;

    union {

#ifdef ENABLE_BACKEND_X11
        backend_x11_t *x11;
#endif
#ifdef ENABLE_BACKEND_WINDOWS
        backend_windows_t *windows;
#endif

    } backends;

} backend_t;

backend_t *create_backend (backend_type_t type);
void destroy_backend (backend_t *backend);

/* how many events are ready to be processed */
int backend_pending (backend_t *backend);

/* wait for and process next event */
void backend_process (backend_t *backend);

/* enter the run loop */
void backend_run (backend_t *backend,
                  idle_callback_t *callback,
                  void *data);

/* request to exit the run loop */
void backend_exit (backend_t *backend);

#endif /* BACKEND_H */
