#include <stdlib.h>

#include "backend.h"

backend_t *create_backend (backend_type_t type) {

    backend_t *backend;

    if (type == BACKEND_AUTO)
        type = BACKEND_X11; /* TODO: for real, detect the most appropriate */

    backend = malloc (sizeof (backend_t));
    backend->type = type;

    switch (type) {

        case BACKEND_X11:
            backend->backends.x11 = create_backend_x11 ();
            break;

        default:
            break;
    }

    return backend;
}

void destroy_backend (backend_t *backend) {

    switch (backend->type) {

        case BACKEND_X11:
            destroy_backend_x11 (backend->backends.x11);
            break;

        default:
            break;
    }

    free (backend);
}

void backend_run (backend_t *backend) {

    switch (backend->type) {

        case BACKEND_X11:
            backend_x11_run (backend->backends.x11);
            break;

        default:
            break;
    }
}

void backend_exit (backend_t *backend) {

    switch (backend->type) {

        case BACKEND_X11:
            backend_x11_exit (backend->backends.x11);
            break;

        default:
            break;
    }
}