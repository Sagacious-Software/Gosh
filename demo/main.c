#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <gosh/window.h>

/* struct to hold the animation state */
typedef struct state_t {

    /* the backend to the windowing system */
    backend_t *backend;

    /* the window to be created */
    window_t *window;

} state_t;

/* render the contents of a window */
void draw (window_t *window) {

    int x, y, width, height;
    uint8_t *pixels;

    /* TODO: do a funky demo */
    width  = window->buffer.region.dimensions.x;
    height = window->buffer.region.dimensions.y;
    pixels = (uint8_t *) window->buffer.pixels;
    for (y = 0; y < height; y++)
        for (x = 0; x < width; x++) {

            int i = x + y * width;

            pixels[i * 4 + 0] = rand (); /* blue */
            pixels[i * 4 + 1] = rand (); /* green */
            pixels[i * 4 + 2] = rand (); /* red */
            pixels[i * 4 + 3] = 255;     /* alpha */
        }
    
    /* update the contents of the window */
    update_window (window);
}

/* called when we receive an event */
void callback (window_t *window, event_t event, void *data) {

    switch (event.type) {

        /* when the window is created */
        case EVENT_CREATE:

            puts ("Hi hi");

            /* fall through */

        /* when vertical blanking occurs */
        case EVENT_VBLANK:

            /* draw the contents of the window */
            draw (window);
            
            break;

        /* when the window is destroyed */
        case EVENT_DESTROY:

            puts ("Bye bye");

            /* exit the application when the window is closed */
            backend_exit (window->backend);
            
            break;

        /* when the window is shown */
        case EVENT_SHOW:

            puts ("Peekaboo :3");

            break;
        
        /* when the window is hidden */
        case EVENT_HIDE:

            puts ("*hides*");

            break;

        /* when the window is moved */
        case EVENT_MOVE:

            printf ("Window was moved: (%d, %d)\n",
                    event.events.move_resize.new_region.offset.x,
                    event.events.move_resize.new_region.offset.y);

            break;

        /* when the window is resized */
        case EVENT_RESIZE:

            printf ("Window was resized: (%d, %d)\n",
                    event.events.move_resize.new_region.dimensions.x,
                    event.events.move_resize.new_region.dimensions.y);

            /* redraw the contents of the window with the new size */
            draw (window);

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

            /* close the window if the user presses escape */
            if (event.events.keyboard.key       == KEYBOARD_KEY_ESCAPE &&
                event.events.keyboard.key_state == KEYBOARD_KEY_PRESSED)
                close_window (window);

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

    /* context to hold all of our program variables */
    state_t state;

    /* the position and dimensions of the window to be created */
    region_t region;

    /* seed the random number generator */
    srand (time (NULL));

    /* create the backend
     * BACKEND_AUTO automatically decides which backend to use
     * MODE_VSYNC means to send vsync events on vsync, useful for animation */
    state.backend = create_backend (BACKEND_AUTO, MODE_VSYNC, NULL, NULL);

    /* set the region on screen for the window to appear
     * offset of 0, 0 will automatically position the window appropriately */
    region.offset.x     = 0;
    region.offset.y     = 0;
    region.dimensions.x = 480;
    region.dimensions.y = 360;

    /* create a window and set the callback */
    state.window = create_window (state.backend, region, "Gosh Demo", callback, &state);

    /* enter the backend run loop until last window is closed */
    backend_run (state.backend);

    /* cleanup and exit */
    destroy_window (state.window);
    destroy_backend (state.backend);

    return EXIT_SUCCESS;
}
