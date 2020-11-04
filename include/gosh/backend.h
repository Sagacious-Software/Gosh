#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>

typedef void idle_callback_t (void *data);

typedef enum backend_type_t {

    BACKEND_AUTO,
    BACKEND_X11,
    BACKEND_WINDOWS,

    NUM_BACKEND_TYPE

} backend_type_t;

typedef struct backend_t {

    /* the type of the backend */
    backend_type_t type;

    /* the backend specific backend instance */
    void *backend;

    /* whether the backend is currenly running */
    bool running;

} backend_t;

/* return NULL on failure to create requested backend */
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
