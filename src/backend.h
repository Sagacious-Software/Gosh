#ifndef BACKEND_H
#define BACKEND_H

typedef struct backend_t {

    int temp;

} backend_t;

backend_t *create_backend ();
void destroy_backend (backend_t *backend);

void backend_run (backend_t *backend);

#endif /* BACKEND_H */
