#ifndef BACKEND_H
#define BACKEND_H

#include "backends/x11/backend.h"

typedef enum backend_type_t {

    BACKEND_AUTO,
    BACKEND_X11,

    NUM_BACKEND_TYPE

} backend_type_t;

typedef struct backend_t {

    /* the type of the backend */
    backend_type_t type;

    union {

        backend_x11_t *x11;

    } backends;

} backend_t;

backend_t *create_backend (backend_type_t type);
void destroy_backend (backend_t *backend);

/* enter the run loop */
void backend_run (backend_t *backend);

/* request to exit the run loop */
void backend_exit (backend_t *backend);

#endif /* BACKEND_H */
