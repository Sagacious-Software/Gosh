#ifndef KEYBOARD_WINDOWS_H
#define KEYBOARD_WINDOWS_H

#include <gosh/keyboard.h>

/* the mappings from windows keycodes to gosh keyboard keys */
extern unsigned int KEYBOARD_KEYS_WINDOWS[];

/* map a windows keyboard key to a gosh keyboard key */
keyboard_key_t keyboard_key_WINDOWS (unsigned int keycode);

#endif /* KEYBOARD_WINDOWS_H */
