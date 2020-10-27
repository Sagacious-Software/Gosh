#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

#include "util.h"

void error_windows (char *title, char *message) {

    fprintf (stderr, "%s\n", message);
    /* TODO: investigate these parameters! */
    MessageBox (NULL, message, title, MB_ICONEXCLAMATION | MB_OK);
    exit (EXIT_FAILURE);
}
