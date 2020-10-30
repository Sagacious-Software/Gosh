#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "util.h"
#include "backend.h"
#include "window.h"
#include "mouse.h"
#include "keyboard.h"

#include <gosh/window.h>
#include <gosh/event.h>

const char WINDOW_CLASS_NAME[] = "GoshWindowClass";

LRESULT CALLBACK process_window (HWND handle,
                                 UINT message,
                                 WPARAM word_parameter,
                                 LPARAM long_parameter) {

    event_t window_event;
    window_windows_t *window;
        
    window = (window_windows_t *) GetWindowLongPtr (handle, GWLP_USERDATA);

    switch (message) {

        case WM_PAINT: {

            int x, y;
            PAINTSTRUCT paint_struct;
            region_t region;

            HDC context = BeginPaint (handle, &paint_struct);
            region = make_region_bounds (paint_struct.rcPaint.left,
                                         paint_struct.rcPaint.top,
                                         paint_struct.rcPaint.right,
                                         paint_struct.rcPaint.bottom);
            /* TODO: instead of painting each pixel, do the blit */
            for (x = region.offset.x; x < region.offset.x + region.dimensions.x; x++)
                for (y = region.offset.y; y < region.offset.y + region.dimensions.y; y++)
                    SetPixelV (context, x, y, *(((uint32_t *) window->window->pixels) + (x + y * region.dimensions.x)));

            EndPaint (handle, &paint_struct);

            return 0;
        }

        case WM_DESTROY:
            
            window_event.type = EVENT_DESTROY;

            PostQuitMessage (0);

            break;

        case WM_SHOWWINDOW:

            window_event.type = EVENT_SHOW;
            window->window->mapped = true;

            break;

        case WM_CLOSE:
            
            window_event.type = EVENT_HIDE;
            window->window->mapped = false;

            DestroyWindow (handle);

            break;

        case WM_MOVE: {

            /* save the old region of the window */
            window_event.events.move_resize.old_region
                = window->window->region;

            /* get the new region of the window */
            window_event.events.move_resize.new_region.offset.x = LOWORD (long_parameter);
            window_event.events.move_resize.new_region.offset.y = HIWORD (long_parameter);

            window_event.type = EVENT_MOVE;

            break;
        }

        case WM_SIZE: {

            /* save the old region of the window */
            window_event.events.move_resize.old_region
                = window->window->region;

            /* get the new region of the window */
            window_event.events.move_resize.new_region.dimensions.x = LOWORD (long_parameter);
            window_event.events.move_resize.new_region.dimensions.y = HIWORD (long_parameter);

            window_event.type = EVENT_RESIZE;

            /* reinitialize the pixel buffer for the new size */
            init_window_windows_buffer (window,
                                        window_event.events.move_resize.new_region);

            break;
        }

        case WM_KEYDOWN:

            /* TODO: text input */

            window_event.type                      = EVENT_KEYBOARD;
            window_event.events.keyboard.key       = keyboard_key_windows (word_parameter);
            window_event.events.keyboard.key_state = KEYBOARD_KEY_PRESSED;

            break;

        case WM_KEYUP:

            window_event.type                      = EVENT_KEYBOARD;
            window_event.events.keyboard.key       = keyboard_key_windows (word_parameter);
            window_event.events.keyboard.key_state = KEYBOARD_KEY_RELEASED;

            break;

        case WM_NCCREATE:
            
            window = (window_windows_t *) ((CREATESTRUCT*) long_parameter)->lpCreateParams;
            SetWindowLongPtr (handle, GWLP_USERDATA, (LONG_PTR) window);
            SetWindowPos (handle, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

            window_event.type = EVENT_CREATE;

        default:
            goto default_proc;
    }

    queue_event_window_windows (window, window_event);

default_proc:
    return DefWindowProc (handle, message, word_parameter, long_parameter);
}

backend_windows_t *create_backend_windows () {

    HINSTANCE handle;
    WNDCLASSEX class;

    /* get the windows application instance handle */
    handle = GetModuleHandle (NULL);

    backend_windows_t *backend_windows = malloc (sizeof (backend_windows_t));
    backend_windows->handle = handle;
    backend_windows->n_windows = 0;

    /* register the window class */
    class.cbSize        = sizeof (WNDCLASSEX);
    class.style         = 0; /* TODO: investigate */
    class.lpfnWndProc   = process_window;
    class.cbClsExtra    = 0;
    class.cbWndExtra    = 0;
    class.hInstance     = handle;
    class.hIcon         = LoadIcon   (NULL, IDI_APPLICATION); /* TODO: investigate */
    class.hCursor       = LoadCursor (NULL, IDC_ARROW); /* TODO: investigate */
    class.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1); /* TODO: investigate */
    class.lpszMenuName  = NULL; /* TODO: investigate */
    class.lpszClassName = WINDOW_CLASS_NAME;
    class.hIconSm       = LoadIcon (NULL, IDI_APPLICATION); /* TODO: investigate */

    if (!RegisterClassEx (&class))
        error_windows ("Gosh Error", "Failed to register Windows window class.");

    return backend_windows;
}

void destroy_backend_windows (backend_windows_t *backend) {

    /* TODO */

    free (backend);
}

void register_window_windows (backend_windows_t *backend, window_windows_t *window) {

    backend->windows[backend->n_windows++] = window;

    /* TODO: handle this more elegantly lol */
    if (backend->n_windows == MAX_WINDOWS)
        fputs ("Warning: opened too many windows!", stderr);
}

int backend_windows_pending (backend_windows_t *backend) {

    return 0; /* TODO */
}

void backend_windows_process (backend_windows_t *backend) {
    
    int i;
    MSG message;
    event_t *event;

    /* TODO: handle when == 0 that means quit */
    if (GetMessage (&message, NULL, 0, 0) > 0) {

        TranslateMessage (&message);
        DispatchMessage (&message);
    }

    /* handle all the queued events for all open windows */
    for (i = 0; i < backend->n_windows; i++) {

        while ((event = get_event_window_windows (backend->windows[i])))
            handle_event (backend->windows[i]->window, *event);
    }
}
