#include <gosh/mouse.h>

const char *MOUSE_BUTTON_NAMES[] = {

    "left",
    "middle",
    "right",

    "scroll up",
    "scroll down",

    "scroll left",
    "scroll right",

    "backwards",
    "forwards",

    "10",
};

const char *mouse_button_name (mouse_button_t button) {

    return MOUSE_BUTTON_NAMES[button];
}
