#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <gosh/window.h>

double noise () {

    return rand () / (double) RAND_MAX;
}

/* struct to hold the animation state */
typedef struct state_t {

    /* the backend to the windowing system */
    backend_t *backend;

    /* the two windows to be created */
    window_t *window_1;
    window_t *window_2;

} state_t;

/* render the contents of a window */
void draw (window_t *window, state_t *state) {

    int x, y, width, height;
    rgba_color_t color;

    /* choose yellow for the first window */
    if (window == state->window_1)
        color = make_color (1, 1, 0, 1);

    /* and magenta for the second window */
    else
        color = make_color (1, 0, 1, 1);

    /* TODO: do a funky demo */
    width  = window->region.dimensions.x;
    height = window->region.dimensions.y;
    for (y = 0; y < height; y++)
        for (x = 0; x < width; x++)
            set_pixel (window,
                       make_point(x, y),
                       multiply_colors (color,
                                        make_color (noise (),
                                                    noise (),
                                                    noise (),
                                                    1)));
    
    /* update the contents of the window */
    update_window (window);
}

/* called when we receive an event */
void callback (window_t *window, event_t event, void *data) {

    state_t *state = (state_t *) data;

    switch (event.type) {

        /* when the window is created */
        case EVENT_CREATE:

            puts ("Hi hi");

            /* fall through */

        /* when vertical blanking occurs */
        case EVENT_VBLANK:

            /* draw the contents of the window */
            draw (window, state);
            
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
            draw (window, state);

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

    /* the position and dimensions of the windows to be created */
    region_t region_1, region_2;

    /* seed the random number generator */
    srand (time (NULL));

    /* create the backend
     * BACKEND_AUTO automatically decides which backend to use */
    if ((state.backend = create_backend (BACKEND_AUTO)) == NULL) {

        fputs ("Failure to create Gosh backend.\n", stderr);
        return EXIT_FAILURE;
    }

    /* set the region on screen for the first window to appear */
    region_1.offset.x     = 32;
    region_1.offset.y     = 32;
    region_1.dimensions.x = 480;
    region_1.dimensions.y = 360;

    /* set the region on screen for the second window to appear */
    region_2.offset.x     = 544;
    region_2.offset.y     = 32;
    region_2.dimensions.x = 480;
    region_2.dimensions.y = 360;

    /* create the first window and set the callback */
    if ((state.window_1 = create_window (state.backend, region_1, "Gosh Demo Window 1", callback, &state)) == NULL) {

        fputs ("Failure to create Gosh window 1.\n", stderr);
        return EXIT_FAILURE;
    }

    /* create the second window and set the callback */
    if ((state.window_2 = create_window (state.backend, region_2, "Gosh Demo Window 2", callback, &state)) == NULL) {

        fputs ("Failure to create Gosh window 2.\n", stderr);
        return EXIT_FAILURE;
    }

    /* TODO
     * run an x11 and windows backend simultaneously
     * in a custom run loop
     * as a second demo */

    /* enter the backend run loop until user exits */
    backend_run (state.backend, NULL, NULL);

    /* cleanup and exit */
    destroy_window (state.window_1);
    destroy_window (state.window_2);
    destroy_backend (state.backend);

    return EXIT_SUCCESS;
}
