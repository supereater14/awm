#ifndef EVENT_ACTIONS_H
#define EVENT_ACTIONS_H

#include "awm.h"

/* Switches to resize mode */
void enter_resize_mode(awm_state *state, XEvent *event);

/* Switches to move mode */
void enter_move_mode(awm_state *state, XEvent *event);

/* Handles a window resizing event */
void resize_window(awm_state *state, XEvent *event);

/* Handles a window moving event */
void move_window(awm_state *state, XEvent *event);

/* Sends a window a close message */
void close_window(awm_state *state, XEvent *event);

#endif
