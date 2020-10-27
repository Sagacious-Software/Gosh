#ifndef KEYBOARD_X11_H
#define KEYBOARD_X11_H

#include <gosh/keyboard.h>

/* the mappings from x11 keycodes to gosh keyboard keys */
extern unsigned int KEYBOARD_KEYS_X11[];

/* map an x11 keyboard key to a gosh keyboard key */
keyboard_key_t keyboard_key_x11 (unsigned int keycode);

#endif /* KEYBOARD_X11_H */
