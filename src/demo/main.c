#include <stdio.h>
#include <stdlib.h>

#include "../window.h"

/*
void draw_region (buffer_t *buffer, region_t region) {


}
*/

void callback (window_t *window, event_t event) {

    switch (event.type) {

        /* when the window is shown */
        case EVENT_MAP:

            puts ("Hi hi");

            break;
        
        /* when the window is hidden */
        case EVENT_UNMAP:

            puts ("Bye bye");

            break;

        /* when a region of the window needs to be redrawn */
        case EVENT_EXPOSE:

            /*
            draw_region (window->buffer, event.events.expose_region);
            */

            break;

        /* when the state of the mouse in the window changed */
        case EVENT_MOUSE:

            /* the state of the mouse is tracked for us */
            printf ("Mouse is at (%d, %d)\n", window->mouse.position.x,
                                              window->mouse.position.y);

            /* but we are also informed of what just changed */
            switch (event.events.mouse.type) {

                /* when the mouse enters the window */
                case EVENT_MOUSE_ENTER:

                    puts ("Mouse entered the window");

                    break;

                /* when the mouse exits the window */
                case EVENT_MOUSE_EXIT:

                    puts ("Mouse exited the window");

                    break;

                /* when the mouse is moved in the window */
                case EVENT_MOUSE_MOVE:

                    printf ("Mouse was moved to (%d, %d)\n",
                            event.events.mouse.position.x,
                            event.events.mouse.position.y);

                    break;

                /* when a mouse button is pressed or released in the window  */
                case EVENT_MOUSE_BUTTON:

                    printf ("Mouse button %s was %s\n",
                            mouse_button_name (event.events.mouse.button),
                            event.events.mouse.button_state == MOUSE_BUTTON_PRESSED
                            ? "PRESSED" : "RELEASED");

                    break;

                /* ignore all other mouse events */
                default:
                    break;
            }

            break;

        /* when the state of the keyboard in the window changed */
        case EVENT_KEYBOARD:

            /* the (physical) state of the keyboard is tracked for us */
            printf ("The Q key (physical) is currently %s\n",
                    window->keyboard.keys[KEYBOARD_KEY_Q] == KEYBOARD_KEY_PRESSED
                    ? "PRESSED" : "RELEASED");

            /* but we are also informed of what just changed */
            printf ("The %s key (physical) was %s\n",
                    keyboard_key_name (event.events.keyboard.key),
                    event.events.keyboard.key_state == KEYBOARD_KEY_PRESSED
                    ? "PRESSED" : "RELEASED");

            break;

        /* when text is entered in the window */
        case EVENT_TEXT:

            printf ("This was typed: \"%s\"\n", event.events.text);

            break;

        /* ignore all other events */
        default:
            break;
    }
}

int main (int argc, char **argv) {

    /* create the backend
     * this automatically decides which backend to use
     * this also automatically makes the connection */
    backend_t *backend = create_backend (BACKEND_AUTO);

    /* create a window and set the callback */
    window_t *window = create_window (backend, callback);

    /* enter the backend run loop until last window is closed */
    backend_run (backend);

    /* cleanup and exit */
    destroy_window (window);
    destroy_backend (backend);

    return EXIT_SUCCESS;
}
