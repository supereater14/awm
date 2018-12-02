#include "event_handler.h"

#include "awm.h"
#include "event_actions.h"

#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>

char *rofi_argv[4] = {"rofi", "-show", "run", NULL};
char *term_argv[2] = {"termite", NULL};

void handle_event(awm_state *state, XEvent *event){
    switch(event->type){
	/* General keyboard commands */
	case KeyPress:
		switch(state->mode){
		    case MODE_NORMAL:
			/* Open rofi */
			/* TODO: generalize this */
			if(event->xkey.keycode
				== XKeysymToKeycode(state->disp, XStringToKeysym("X"))){
			    if(!fork()){
				setsid();
				execvp(rofi_argv[0], rofi_argv);
			    }
			/* Exit awm */
			} else if(event->xkey.keycode
				== XKeysymToKeycode(state->disp, XStringToKeysym("E"))){
				exit(0);
			/* Open termite */
			/* TODO: generalize this */
			} else if(event->xkey.keycode
				== XKeysymToKeycode(state->disp, XStringToKeysym("Return"))){
			    if(!fork()){
				setsid();
				execvp(term_argv[0], term_argv);
			    }
			/* Enter resize mode */
			} else if(event->xkey.keycode
				== XKeysymToKeycode(state->disp, XStringToKeysym("R"))){
				if(event->xbutton.subwindow != None){
					enter_resize_mode(state, event);
				}
			/* Close window */
			} else if(event->xkey.keycode
				== XKeysymToKeycode(state->disp, XStringToKeysym("Q"))){
				close_window(state, event);
			}
			break;
		    default:
			break;
		}
	    break;
	/* When the mouse button is pressed */
	case ButtonPress:
		switch(state->mode){
		    case MODE_NORMAL:
			if(event->xbutton.subwindow != None){
			    enter_move_mode(state, event);
			}
			break;
		    default:
			break;
		}
	    break;
	/* When the mouse is moved */
	case MotionNotify:
		switch(state->mode){
		    case MODE_MOVE:
			{
			    move_window(state, event);
			}
			break;
		    case MODE_RESIZE:
			{
			    resize_window(state, event);
			}
		    default:
			break;
		}
	    break;
	/* When the mouse is released, move to normal mode */
	case ButtonRelease:
		switch(state->mode){
		    case MODE_RESIZE:
		    case MODE_MOVE:
			    state->mode = MODE_NORMAL;
			    XUngrabPointer(state->disp, CurrentTime);
			break;
		    default:
			break;
		}
	    break;
	default:
	    break;
    }
}
