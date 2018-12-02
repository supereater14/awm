#ifndef AWM_H
#define AWM_H

#include <X11/Xlib.h>

/* Stores the general state of the window manager */
typedef struct {
    /* Current operating mode */
    enum {
	/* Normal mode, listens for key commands */
	MODE_NORMAL,
	/* Move move, moves windows around */
	MODE_MOVE,
	/* Resize mode, resizes windows */
	MODE_RESIZE
    } mode;
    /* The event which triggered the last change to a non-normal mode */
    XEvent mode_trigger_event;
    /* The window which was active at the last mode change */
    Window selected_window;
    /* Attributes of selected_window */
    XWindowAttributes window_attrib;

    /* The display we are managing */
    Display *disp;
    /* The root window of the display */
    Window root;
} awm_state;

#endif
