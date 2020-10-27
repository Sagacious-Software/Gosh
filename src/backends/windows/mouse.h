#ifndef MOUSE_WINDOWS_H
#define MOUSE_WINDOWS_H

#include <gosh/mouse.h>

/* the mappings from windows mouse buttons to gosh mouse buttons */
extern unsigned int MOUSE_BUTTONS_WINDOWS[];

/* map a windows mouse button to a gosh mouse button */
mouse_button_t mouse_button_windows (unsigned int button);

#endif /* MOUSE_WINDOWS_H */
