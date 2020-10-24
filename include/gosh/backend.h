#ifndef BACKEND_H
#define BACKEND_H

#include "backends/x11/backend.h"

typedef enum backend_type_t {

    BACKEND_AUTO,
    BACKEND_X11,

    NUM_BACKEND_TYPE

} backend_type_t;

typedef enum backend_mode_t {

    MODE_SYNC,  /* idle until an event is received
                   this is ideal for applications that do not
                   need to draw continuously, e.g. animations
                   or otherwise make use of idle cpu time */
    MODE_ASYNC, /* call idle function when no other event is available
                   this is ideal for having maximum
                   control over idle cpu time */
    MODE_VSYNC, /* send vsync events in sync with the monitor's refresh rate
                   this is ideal for applications that need to
                   draw continuously, e.g. animations */

    NUM_BACKEND_MODE

} backend_mode_t;

typedef struct backend_t backend_t;
typedef void backend_idle_callback_t (backend_t *backend);

struct backend_t {

    /* the type of the backend */
    backend_type_t type;

    /* the event polling mode */
    backend_mode_t mode;

    /* the function that is called during idle cpu time in async mode */
    backend_idle_callback_t *idle;

    union {

        backend_x11_t *x11;

    } backends;

};

backend_t *create_backend (backend_type_t type,
                           backend_mode_t mode,
                           backend_idle_callback_t *idle_callback);
void destroy_backend (backend_t *backend);

/* enter the run loop */
void backend_run (backend_t *backend);

/* request to exit the run loop */
void backend_exit (backend_t *backend);

/* call the user specified idle function */
void backend_idle (backend_t *backend);

#endif /* BACKEND_H */
