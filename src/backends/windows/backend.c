#include <stdlib.h>
#include <stdio.h>

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

    /* TODO */

    /*
    event_t window_event;
    handle_event (window->window, window_event);
    */

    /* TODO: fill this all out */
    switch (message) {

        case WM_CLOSE:
            
            /* TODO */
            DestroyWindow (handle);

            break;

        case WM_DESTROY:
            
            /* TODO */
            PostQuitMessage (0);

            break;

        default:
            return DefWindowProc (handle, message, word_parameter, long_parameter);
    }

    return 0;
}

backend_windows_t *create_backend_windows () {

    HINSTANCE handle;
    WNDCLASSEX class;

    /* get the windows application instance handle */
    handle = GetModuleHandle (NULL);

    backend_windows_t *backend_windows = malloc (sizeof (backend_windows_t));
    backend_windows->handle = handle;

    /* register the window class */
    class.cbSize        = sizeof (WNDCLASSEX);
    class.style         = 0; /* TODO: investigate */
    class.lpfnWndProc  = process_window;
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

int backend_windows_pending (backend_windows_t *backend) {

    return 0; /* TODO */
}

void backend_windows_process (backend_windows_t *backend) {
    
    MSG message;

    /* TODO: handle when == 0 that means quit */
    if (GetMessage (&message, NULL, 0, 0) > 0) {

        TranslateMessage (&message);
        DispatchMessage (&message);
    }
}
