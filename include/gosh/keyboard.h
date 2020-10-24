#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "util.h"

typedef enum keyboard_key_t {

    /* Function keys */
    KEYBOARD_KEY_F1,
    KEYBOARD_KEY_F2,
    KEYBOARD_KEY_F3,
    KEYBOARD_KEY_F4,
    KEYBOARD_KEY_F5,
    KEYBOARD_KEY_F6,
    KEYBOARD_KEY_F7,
    KEYBOARD_KEY_F8,
    KEYBOARD_KEY_F9,
    KEYBOARD_KEY_F10,
    KEYBOARD_KEY_F11,
    KEYBOARD_KEY_F12,

    /* Function-specific keys */
    KEYBOARD_KEY_BACKSPACE,
    KEYBOARD_KEY_BREAK,
    KEYBOARD_KEY_CAPS_LOCK,
    KEYBOARD_KEY_DELETE,
    KEYBOARD_KEY_END,
    KEYBOARD_KEY_ENTER,
    KEYBOARD_KEY_ESCAPE,
    KEYBOARD_KEY_HOME,
    KEYBOARD_KEY_INSERT, /* https://tenor.com/view/anime-smirk-evil-grin-eyebrow-raise-gif-16738193 */
    KEYBOARD_KEY_LEFT_ALT,
    KEYBOARD_KEY_LEFT_CONTROL,
    KEYBOARD_KEY_LEFT_SHIFT,
    KEYBOARD_KEY_PAGE_DOWN,
    KEYBOARD_KEY_PAGE_UP,
    KEYBOARD_KEY_PAUSE,
    KEYBOARD_KEY_RIGHT_ALT,
    KEYBOARD_KEY_RIGHT_CONTROL,
    KEYBOARD_KEY_RIGHT_SHIFT,

    /* Special character keys */
    KEYBOARD_KEY_APOSTROPHE,
    KEYBOARD_KEY_BACKSLASH,
    KEYBOARD_KEY_BACKTICK,
    KEYBOARD_KEY_COMMA,
    KEYBOARD_KEY_EQUALS,
    KEYBOARD_KEY_LEFT_BRACKET,
    KEYBOARD_KEY_MINUS,
    KEYBOARD_KEY_PERIOD,
    KEYBOARD_KEY_RIGHT_BRACKET,
    KEYBOARD_KEY_SEMICOLON,
    KEYBOARD_KEY_SLASH,
    KEYBOARD_KEY_TAB,
    KEYBOARD_KEY_SPACE,

    /* Number row keys */
    KEYBOARD_KEY_1,
    KEYBOARD_KEY_2,
    KEYBOARD_KEY_3,
    KEYBOARD_KEY_4,
    KEYBOARD_KEY_5,
    KEYBOARD_KEY_6,
    KEYBOARD_KEY_7,
    KEYBOARD_KEY_8,
    KEYBOARD_KEY_9,
    KEYBOARD_KEY_0,

    /* Character keys */
    KEYBOARD_KEY_Q,
    KEYBOARD_KEY_W,
    KEYBOARD_KEY_E,
    KEYBOARD_KEY_R,
    KEYBOARD_KEY_T,
    KEYBOARD_KEY_Y,
    KEYBOARD_KEY_U,
    KEYBOARD_KEY_I,
    KEYBOARD_KEY_O,
    KEYBOARD_KEY_P,
    KEYBOARD_KEY_A,
    KEYBOARD_KEY_S,
    KEYBOARD_KEY_D,
    KEYBOARD_KEY_F,
    KEYBOARD_KEY_G,
    KEYBOARD_KEY_H,
    KEYBOARD_KEY_J,
    KEYBOARD_KEY_K,
    KEYBOARD_KEY_L,
    KEYBOARD_KEY_Z,
    KEYBOARD_KEY_X,
    KEYBOARD_KEY_C,
    KEYBOARD_KEY_V,
    KEYBOARD_KEY_B,
    KEYBOARD_KEY_N,
    KEYBOARD_KEY_M,

    /* Keypad */
    KEYPAD_KEY_0,
    KEYPAD_KEY_1,
    KEYPAD_KEY_2,
    KEYPAD_KEY_3,
    KEYPAD_KEY_4,
    KEYPAD_KEY_5,
    KEYPAD_KEY_6,
    KEYPAD_KEY_7,
    KEYPAD_KEY_8,
    KEYPAD_KEY_9,

    KEYPAD_KEY_ASTERISK,
    KEYPAD_KEY_ENTER,
    KEYPAD_KEY_MINUS,
    KEYPAD_KEY_NUM_LOCK,
    KEYPAD_KEY_PERIOD,
    KEYPAD_KEY_PLUS,
    KEYPAD_KEY_SLASH,

    NUM_KEYBOARD_KEY

} keyboard_key_t;

/* the names of the keyboard keys */
extern const char *KEYBOARD_KEY_NAMES[];

/* get the name of a keyboard key */
const char *keyboard_key_name (keyboard_key_t key);

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

#endif /* KEYBOARD_H */
