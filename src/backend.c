#include <stdlib.h>

#include <gosh/backend.h>

backend_t *create_backend (backend_type_t type) {

    backend_t *backend;

    if (type == BACKEND_AUTO)
#ifdef ENABLE_BACKEND_X11
        type = BACKEND_X11;
#endif
#ifdef ENABLE_BACKEND_WINDOWS
        type = BACKEND_WINDOWS;
#endif
    /* TODO: or allow environment variable overrides
     * use the GOSH_BACKEND variable */

    backend = malloc (sizeof (backend_t));
    backend->type = type;
    backend->running = true;

    switch (type) {

#ifdef ENABLE_BACKEND_X11
        case BACKEND_X11:
            backend->backends.x11 = create_backend_x11 (backend);
            break;

#endif
#ifdef ENABLE_BACKEND_WINDOWS
        case BACKEND_WINDOWS:
            backend->backends.windows = create_backend_windows (backend);
            break;

#endif
        default:
            break;
    }

    return backend;
}

void destroy_backend (backend_t *backend) {

    switch (backend->type) {

#ifdef ENABLE_BACKEND_X11
        case BACKEND_X11:
            destroy_backend_x11 (backend->backends.x11);
            break;

#endif
#ifdef ENABLE_BACKEND_WINDOWS
        case BACKEND_WINDOWS:
            destroy_backend_windows (backend->backends.windows);
            break;

#endif
        default:
            break;
    }

    free (backend);
}

int backend_pending (backend_t *backend) {

    switch (backend->type) {

#ifdef ENABLE_BACKEND_X11
        case BACKEND_X11:
            return backend_x11_pending (backend->backends.x11);

#endif
#ifdef ENABLE_BACKEND_WINDOWS
        case BACKEND_WINDOWS:
            return backend_windows_pending (backend->backends.windows);

#endif
        default:
            return false;
    }
}

void backend_process (backend_t *backend) {

    switch (backend->type) {

#ifdef ENABLE_BACKEND_X11
        case BACKEND_X11:
            backend_x11_process (backend->backends.x11);
            break;

#endif
#ifdef ENABLE_BACKEND_WINDOWS
        case BACKEND_WINDOWS:
            backend_windows_process (backend->backends.windows);
            break;

#endif
        default:
            break;
    }
}

void backend_run (backend_t *backend, idle_callback_t *callback, void *data) {

    while (backend->running) {
        
        if (callback && backend_pending (backend) == 0) {

            callback (data);
            continue;
        }

        backend_process (backend);
    }
}

void backend_exit (backend_t *backend) {

    backend->running = false;
}
