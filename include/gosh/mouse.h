#ifndef MOUSE_H
#define MOUSE_H

#include "util.h"

typedef enum mouse_button_t {

    MOUSE_LEFT,
    MOUSE_MIDDLE,
    MOUSE_RIGHT,

    NUM_MOUSE_BUTTON

} mouse_button_t;

typedef enum mouse_button_state_t {

    MOUSE_BUTTON_PRESSED,
    MOUSE_BUTTON_RELEASED,

    NUM_MOUSE_BUTTON_STATE

} mouse_button_state_t;

/* the state of the mouse in a window */
typedef struct mouse_t {

    /* the position of the mouse in the window relative to the top left corner */
    point_t position;

    /* the states of the mouse buttons */
    mouse_button_state_t buttons[NUM_MOUSE_BUTTON];

} mouse_t;

/* get the name of a mouse button */
const char *mouse_button_name (mouse_button_t button);

#endif /* MOUSE_H */