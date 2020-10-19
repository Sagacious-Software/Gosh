#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "util.h"

typedef enum keyboard_key_t {

    KEYBOARD_KEY_Q,

    NUM_KEYBOARD_KEY

} keyboard_key_t;

typedef enum keyboard_key_state_t {

    KEYBOARD_KEY_PRESSED,
    KEYBOARD_KEY_RELEASED,

    NUM_KEYBOARD_KEY_STATE

} keyboard_key_state_t;

/* the state of the keyboard in a window */
typedef struct keyboard_t {

    /* the states of the keyboard keys */
    keyboard_key_state_t keys[NUM_KEYBOARD_KEY_STATE];

} keyboard_t;

/* get the name of a keyboard key */
const char *keyboard_key_name (keyboard_key_t key);

#endif /* KEYBOARD_H */
