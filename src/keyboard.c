#include <gosh/keyboard.h>

const char *KEYBOARD_KEY_NAMES[] = {

    /* Function keys */
    "f1",
    "f2",
    "f3",
    "f4",
    "f5",
    "f6",
    "f7",
    "f8",
    "f9",
    "f10",
    "f11",
    "f12",

    /* Function-specific keys */
    "backspace",
    "caps lock",
    "delete",
    "end",
    "enter",
    "escape",
    "home",
    "insert",
    "left alt",
    "left control",
    "left shift",
    "page down",
    "page up",
    "pause",
    "right alt",
    "right control",
    "right shift",

    /* Special character keys */
    "apostrophe",
    "backslash",
    "backtick",
    "comma",
    "equals",
    "left bracket",
    "minus",
    "period",
    "right bracket",
    "semicolon",
    "forward slash",
    "tab",
    "space",

    /* Number row keys */
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",

    /* Character keys */
    "q",
    "w",
    "e",
    "r",
    "t",
    "y",
    "u",
    "i",
    "o",
    "p",
    "a",
    "s",
    "d",
    "f",
    "g",
    "h",
    "j",
    "k",
    "l",
    "z",
    "x",
    "c",
    "v",
    "b",
    "n",
    "m",

    /* Keypad */
    "keypad 0",
    "keypad 1",
    "keypad 2",
    "keypad 3",
    "keypad 4",
    "keypad 5",
    "keypad 6",
    "keypad 7",
    "keypad 8",
    "keypad 9",

    "keypad astrerisk",
    "keypad enter",
    "keypad minus",
    "keypad num luck",
    "keypad period",
    "keypad plus",
    "keypad slash",

    "unknown"
};

const char *keyboard_key_name (keyboard_key_t key) {

    return KEYBOARD_KEY_NAMES[key];
}
