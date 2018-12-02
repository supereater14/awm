#include "event_actions.h"

#include "awm.h"

#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>

void enter_resize_mode(awm_state *state, XEvent *event){
    /* Update internal state */
    state->mode = MODE_RESIZE;
    state->selected_window = event->xbutton.subwindow;
    state->mode_trigger_event = *event;
    XGetWindowAttributes(state->disp, event->xbutton.subwindow,
	    &(state->window_attrib));

    /* Raise the selected window */
    XRaiseWindow(state->disp, event->xbutton.subwindow);

    /* Listen for mouse events so we can resize */
    XGrabPointer(state->disp, event->xbutton.subwindow, True,
	    PointerMotionMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync,
	    None, None, CurrentTime);
}
void enter_move_mode(awm_state *state, XEvent *event){
    /* Update internal state */
    state->mode = MODE_MOVE;
    state->selected_window = event->xbutton.subwindow;
    state->mode_trigger_event = *event;
    XGetWindowAttributes(state->disp, event->xbutton.subwindow,
	    &(state->window_attrib));

    /* Raise selected window */
    XRaiseWindow(state->disp, event->xbutton.subwindow);

    /* Listen for mouse events so we can move */
    XGrabPointer(state->disp, event->xbutton.subwindow, True,
	    PointerMotionMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync,
	    None, None, CurrentTime);
}
void resize_window(awm_state *state, XEvent *event){
    /* Clean Event buffer */
    while(XCheckTypedEvent(state->disp, MotionNotify, event));

    /* Calculate new window dimensions */
    int width = event->xbutton.x_root - state->window_attrib.x;
    int height = event->xbutton.y_root - state->window_attrib.y;

    /* Disallow dimensions <= 0 */
    if(width <= 0){
	width = 1;
    }
    if(height <= 0){
	height = 1;
    }

    /* Resize the selected window */
    XResizeWindow(state->disp, state->selected_window, width, height);
}
void move_window(awm_state *state, XEvent *event){
    /* Clean Event buffer */
    while(XCheckTypedEvent(state->disp, MotionNotify, event));

    /* Find offset to move */
    int x_diff = event->xbutton.x_root
	- state->mode_trigger_event.xbutton.x_root;
    int y_diff = event->xbutton.y_root
	- state->mode_trigger_event.xbutton.y_root;

    /* Move window */
    XMoveWindow(state->disp,
	    state->selected_window,
	    state->window_attrib.x + x_diff,
	    state->window_attrib.y + y_diff);
}
void close_window(awm_state *state, XEvent *event){
    /* Close event struct */
    XEvent close_event;

    /* Clear struct values */
    memset(&close_event, 0, sizeof(XEvent));

    /* Prepare message */
    close_event.xclient.type = ClientMessage;
    close_event.xclient.window = event->xkey.subwindow;
    close_event.xclient.message_type = XInternAtom(state->disp, "WM_PROTOCOLS", True);
    close_event.xclient.format = 32;
    close_event.xclient.data.l[0] = XInternAtom(state->disp, "WM_DELETE_WINDOW", False);
    close_event.xclient.data.l[1] = CurrentTime;

    /* Send message */
    XSendEvent(state->disp, event->xkey.subwindow, False, NoEventMask, &close_event);
}
