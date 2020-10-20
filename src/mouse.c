#include "mouse.h"

const char *mouse_button_name (mouse_button_t button) {

    switch (button) {

        case MOUSE_LEFT:
            return "left mouse button";

        case MOUSE_MIDDLE:
            return "middle mouse button";

        case MOUSE_RIGHT:
            return "right mouse button";

        default:
            return "unknown mouse button";
    }
}
