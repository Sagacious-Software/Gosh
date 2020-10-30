#ifndef KEYBOARD_WINDOWS_H
#define KEYBOARD_WINDOWS_H

#include <windows.h>

#include <gosh/keyboard.h>

/* the mappings from windows keycodes to gosh keyboard keys */
extern WPARAM KEYBOARD_KEYS_WINDOWS[];

/* map a windows keyboard key to a gosh keyboard key */
keyboard_key_t keyboard_key_windows (WPARAM keycode);

#endif /* KEYBOARD_WINDOWS_H */
