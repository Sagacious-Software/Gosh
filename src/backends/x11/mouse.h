#ifndef MOUSE_X11_H
#define MOUSE_X11_H

#include <gosh/mouse.h>

/* the mappings from x11 mouse buttons to gosh mouse buttons */
extern unsigned int MOUSE_BUTTONS_X11[];

/* map an x11 mouse button to a gosh mouse button */
mouse_button_t mouse_button_x11 (unsigned int button);

#endif /* MOUSE_X11_H */
