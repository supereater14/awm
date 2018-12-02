#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "awm.h"

#include <X11/Xlib.h>

/* Processes an event */
void handle_event(awm_state *state, XEvent *event);

#endif
