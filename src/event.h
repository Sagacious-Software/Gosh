#ifndef EVENT_H
#define EVENT_H

#include "mouse.h"
#include "keyboard.h"
#include "util.h"

typedef enum event_type_t {

    EVENT_OPEN,     /* when the window is initially opened */
    EVENT_CLOSE,    /* when the window is about to close */
    EVENT_EXPOSE,   /* when a region of the window needs to be redrawn */
    EVENT_MOUSE,    /* when the state of the mouse in the window changed */
    EVENT_KEYBOARD, /* when the state of the keyboard in the window changed */
    EVENT_TEXT,     /* when text is entered in the window */

    NUM_EVENT_TYPE

} event_type_t;

typedef enum mouse_event_type_t {

    EVENT_MOUSE_ENTER,
    EVENT_MOUSE_EXIT,
    EVENT_MOUSE_MOVE,
    EVENT_MOUSE_BUTTON,

    NUM_MOUSE_EVENT_TYPE

} mouse_event_type_t;

typedef struct event_t {

    /* the type of the event */
    event_type_t type;

    union {

        /* the region of the window that was exposed for expose events */
        region_t expose_region;
        
        /* information about the mouse and what changed for mouse events */
        struct {

            /* what type of mouse event occurred */
            mouse_event_type_t type;

            /* the current position of the mouse
             * this will be valid for all mouse events */
            point_t position;

            /* which mouse button was changed */
            mouse_button_t button;

            /* the new state of the mouse button that was changed */
            mouse_button_state_t button_state;

        } mouse;

        /* information about the keyboard and what changed for keyboard events */
        struct {

            /* which key was changed */
            keyboard_key_t key;

            /* the new state of the key that was changed */
            keyboard_key_state_t key_state;

        } keyboard;

        /* the text that was entered for text events */
        const char *text;

    } data;

} event_t;

#endif /* EVENT_H */
