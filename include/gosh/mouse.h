#ifndef MOUSE_H
#define MOUSE_H

#include "util.h"

typedef enum mouse_button_t {

    MOUSE_LEFT,
    MOUSE_MIDDLE,
    MOUSE_RIGHT,

    MOUSE_SCROLL_UP,
    MOUSE_SCROLL_DOWN,

    MOUSE_SCROLL_LEFT,
    MOUSE_SCROLL_RIGHT,

    MOUSE_BACKWARDS,
    MOUSE_FORWARDS,

    MOUSE_10, /* TODO(Sherlock): Unravel the mystery that is Button 10! */

    NUM_MOUSE_BUTTON

} mouse_button_t;

/* the names of the mouse buttons */
extern const char *MOUSE_BUTTON_NAMES[];

/* get the name of a mouse button */
const char *mouse_button_name (mouse_button_t button);

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

#endif /* MOUSE_H */
