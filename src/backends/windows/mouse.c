#include "mouse.h"

/* TODO: the type here */
unsigned int MOUSE_BUTTONS_WINDOWS[] = {

    /* TODO */

    MOUSE_LEFT,
    MOUSE_MIDDLE,
    MOUSE_RIGHT,
    MOUSE_SCROLL_UP,
    MOUSE_SCROLL_DOWN,
};

mouse_button_t mouse_button_windows (unsigned int button) {

    /* TODO: the type */
    if (button >= sizeof (MOUSE_BUTTONS_WINDOWS) / sizeof (unsigned int))
        return MOUSE_UNKNOWN;

    return MOUSE_BUTTONS_WINDOWS[button];
}
