#include <gosh/keyboard.h>

const char *keyboard_key_name (keyboard_key_t key) {

    switch (key) {

        case KEYBOARD_KEY_Q:
            return "keyboard key Q";

        default:
            return "unknown keyboard key";
    }
}
