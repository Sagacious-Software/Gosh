#include <X11/Xlib.h>

#include "keyboard.h"

unsigned int KEYBOARD_KEYS_X11[] = {

    /* TODO: finish replacing unknowns here that correspond to 
     * members of the key_key_t array in "include/gosh/keyboard.h"
     * (leave the rest as unknowns) */
    KEYBOARD_KEY_UNKNOWN,       /* 0   */
    KEYBOARD_KEY_UNKNOWN,       /* 1   */
    KEYBOARD_KEY_UNKNOWN,       /* 2   */
    KEYBOARD_KEY_UNKNOWN,       /* 3   */
    KEYBOARD_KEY_UNKNOWN,       /* 4   */
    KEYBOARD_KEY_UNKNOWN,       /* 5   */
    KEYBOARD_KEY_UNKNOWN,       /* 6   */
    KEYBOARD_KEY_UNKNOWN,       /* 7   */
    KEYBOARD_KEY_UNKNOWN,       /* 8   */
    KEYBOARD_KEY_CAPS_LOCK,     /* 9   */
    KEYBOARD_KEY_UNKNOWN,       /* 10  */
    KEYBOARD_KEY_UNKNOWN,       /* 11  */
    KEYBOARD_KEY_UNKNOWN,       /* 12  */
    KEYBOARD_KEY_UNKNOWN,       /* 13  */
    KEYBOARD_KEY_UNKNOWN,       /* 14  */
    KEYBOARD_KEY_UNKNOWN,       /* 15  */
    KEYBOARD_KEY_UNKNOWN,       /* 16  */
    KEYBOARD_KEY_UNKNOWN,       /* 17  */
    KEYBOARD_KEY_UNKNOWN,       /* 18  */
    KEYBOARD_KEY_UNKNOWN,       /* 19  */
    KEYBOARD_KEY_UNKNOWN,       /* 20  */
    KEYBOARD_KEY_UNKNOWN,       /* 21  */
    KEYBOARD_KEY_BACKSPACE,     /* 22  */
    KEYBOARD_KEY_UNKNOWN,       /* 23  */
    KEYBOARD_KEY_Q,             /* 24  */
    KEYBOARD_KEY_UNKNOWN,       /* 25  */
    KEYBOARD_KEY_UNKNOWN,       /* 26  */
    KEYBOARD_KEY_UNKNOWN,       /* 27  */
    KEYBOARD_KEY_UNKNOWN,       /* 28  */
    KEYBOARD_KEY_UNKNOWN,       /* 29  */
    KEYBOARD_KEY_UNKNOWN,       /* 30  */
    KEYBOARD_KEY_UNKNOWN,       /* 31  */
    KEYBOARD_KEY_UNKNOWN,       /* 32  */
    KEYBOARD_KEY_UNKNOWN,       /* 33  */
    KEYBOARD_KEY_UNKNOWN,       /* 34  */
    KEYBOARD_KEY_UNKNOWN,       /* 35  */
    KEYBOARD_KEY_UNKNOWN,       /* 36  */
    KEYBOARD_KEY_LEFT_CONTROL,  /* 37  */
    KEYBOARD_KEY_UNKNOWN,       /* 38  */
    KEYBOARD_KEY_UNKNOWN,       /* 39  */
    KEYBOARD_KEY_UNKNOWN,       /* 40  */
    KEYBOARD_KEY_UNKNOWN,       /* 41  */
    KEYBOARD_KEY_UNKNOWN,       /* 42  */
    KEYBOARD_KEY_UNKNOWN,       /* 43  */
    KEYBOARD_KEY_UNKNOWN,       /* 44  */
    KEYBOARD_KEY_UNKNOWN,       /* 45  */
    KEYBOARD_KEY_UNKNOWN,       /* 46  */
    KEYBOARD_KEY_UNKNOWN,       /* 47  */
    KEYBOARD_KEY_UNKNOWN,       /* 48  */
    KEYBOARD_KEY_UNKNOWN,       /* 49  */
    KEYBOARD_KEY_LEFT_SHIFT,    /* 50  */
    KEYBOARD_KEY_UNKNOWN,       /* 51  */
    KEYBOARD_KEY_UNKNOWN,       /* 52  */
    KEYBOARD_KEY_UNKNOWN,       /* 53  */
    KEYBOARD_KEY_UNKNOWN,       /* 54  */
    KEYBOARD_KEY_UNKNOWN,       /* 55  */
    KEYBOARD_KEY_UNKNOWN,       /* 56  */
    KEYBOARD_KEY_UNKNOWN,       /* 57  */
    KEYBOARD_KEY_UNKNOWN,       /* 58  */
    KEYBOARD_KEY_UNKNOWN,       /* 59  */
    KEYBOARD_KEY_UNKNOWN,       /* 60  */
    KEYBOARD_KEY_UNKNOWN,       /* 61  */
    KEYBOARD_KEY_RIGHT_SHIFT,   /* 62  */
    KEYBOARD_KEY_UNKNOWN,       /* 63  */
    KEYBOARD_KEY_LEFT_ALT,      /* 64  */
    KEYBOARD_KEY_UNKNOWN,       /* 65  */
    KEYBOARD_KEY_ESCAPE,        /* 66  */
    KEYBOARD_KEY_F1,            /* 67  */
    KEYBOARD_KEY_F2,            /* 68  */
    KEYBOARD_KEY_F3,            /* 69  */
    KEYBOARD_KEY_F4,            /* 70  */
    KEYBOARD_KEY_F5,            /* 71  */
    KEYBOARD_KEY_F6,            /* 72  */
    KEYBOARD_KEY_F7,            /* 73  */
    KEYBOARD_KEY_F8,            /* 74  */
    KEYBOARD_KEY_F9,            /* 75  */
    KEYBOARD_KEY_F10,           /* 76  */
    KEYBOARD_KEY_UNKNOWN,       /* 77  */
    KEYBOARD_KEY_UNKNOWN,       /* 78  */
    KEYBOARD_KEY_UNKNOWN,       /* 79  */
    KEYBOARD_KEY_UNKNOWN,       /* 80  */
    KEYBOARD_KEY_UNKNOWN,       /* 81  */
    KEYBOARD_KEY_UNKNOWN,       /* 82  */
    KEYBOARD_KEY_UNKNOWN,       /* 83  */
    KEYBOARD_KEY_UNKNOWN,       /* 84  */
    KEYBOARD_KEY_UNKNOWN,       /* 85  */
    KEYBOARD_KEY_UNKNOWN,       /* 86  */
    KEYBOARD_KEY_UNKNOWN,       /* 87  */
    KEYBOARD_KEY_UNKNOWN,       /* 88  */
    KEYBOARD_KEY_UNKNOWN,       /* 89  */
    KEYBOARD_KEY_UNKNOWN,       /* 90  */
    KEYBOARD_KEY_UNKNOWN,       /* 91  */
    KEYBOARD_KEY_UNKNOWN,       /* 92  */
    KEYBOARD_KEY_UNKNOWN,       /* 93  */
    KEYBOARD_KEY_UNKNOWN,       /* 94  */
    KEYBOARD_KEY_F11,           /* 95  */
    KEYBOARD_KEY_F12,           /* 96  */
    KEYBOARD_KEY_UNKNOWN,       /* 97  */
    KEYBOARD_KEY_UNKNOWN,       /* 98  */
    KEYBOARD_KEY_UNKNOWN,       /* 99  */
    KEYBOARD_KEY_UNKNOWN,       /* 100 */
    KEYBOARD_KEY_UNKNOWN,       /* 101 */
    KEYBOARD_KEY_UNKNOWN,       /* 102 */
    KEYBOARD_KEY_UNKNOWN,       /* 103 */
    KEYBOARD_KEY_UNKNOWN,       /* 104 */
    KEYBOARD_KEY_RIGHT_CONTROL, /* 105 */
    KEYBOARD_KEY_UNKNOWN,       /* 106 */
    KEYBOARD_KEY_UNKNOWN,       /* 107 */
    KEYBOARD_KEY_RIGHT_ALT,     /* 108 */
    KEYBOARD_KEY_UNKNOWN,       /* 109 */
    KEYBOARD_KEY_HOME,          /* 110 */
    KEYBOARD_KEY_UNKNOWN,       /* 111 */
    KEYBOARD_KEY_PAGE_UP,       /* 112 */
    KEYBOARD_KEY_UNKNOWN,       /* 113 */
    KEYBOARD_KEY_UNKNOWN,       /* 114 */
    KEYBOARD_KEY_END,           /* 115 */
    KEYBOARD_KEY_UNKNOWN,       /* 116 */
    KEYBOARD_KEY_PAGE_DOWN,     /* 117 */
    KEYBOARD_KEY_INSERT,        /* 118 */
    KEYBOARD_KEY_DELETE,        /* 119 */
    KEYBOARD_KEY_UNKNOWN,       /* 120 */
    KEYBOARD_KEY_UNKNOWN,       /* 121 */
    KEYBOARD_KEY_UNKNOWN,       /* 122 */
    KEYBOARD_KEY_UNKNOWN,       /* 123 */
    KEYBOARD_KEY_UNKNOWN,       /* 124 */
    KEYBOARD_KEY_UNKNOWN,       /* 125 */
    KEYBOARD_KEY_UNKNOWN,       /* 126 */
    KEYBOARD_KEY_PAUSE,         /* 127 */
};

keyboard_key_t keyboard_key_x11 (unsigned int keycode) {

    if (keycode >= sizeof (KEYBOARD_KEYS_X11) / sizeof (unsigned int))
        return KEYBOARD_KEY_UNKNOWN;

    return KEYBOARD_KEYS_X11[keycode];
}
