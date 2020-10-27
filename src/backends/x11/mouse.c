#include <X11/Xlib.h>

#include "mouse.h"

unsigned int MOUSE_BUTTONS_X11[] = {

    MOUSE_LEFT,
    MOUSE_MIDDLE,
    MOUSE_RIGHT,
    MOUSE_SCROLL_UP,
    MOUSE_SCROLL_DOWN,
};

mouse_button_t mouse_button_x11 (unsigned int button) {

    if (button >= sizeof (MOUSE_BUTTONS_X11) / sizeof (unsigned int))
        return MOUSE_UNKNOWN;

    return MOUSE_BUTTONS_X11[button];
}
