#include "awm.h"
#include "event_handler.h"
#include "keybind.h"
#include "reaper.h"

#include <stdlib.h>
#include <X11/Xlib.h>

int main(){
    awm_state state;
    XEvent event;

    /* Clear State */
    state.mode = MODE_NORMAL;

    /* Setup X11 */
    if(!(state.disp = XOpenDisplay(0x00))){
	return -1;
    }
    state.root = DefaultRootWindow(state.disp);

    /* Setup Keybinds */
    setup_keybinds(&state);

    /* Stop leaving zombies all over the place */
    setup_reaper();

    /* Begin Main Loop */
    for(;;){
	/* Grab the next event in the queue */
	XNextEvent(state.disp, &event);

	/* Process the event */
	handle_event(&state, &event);
    }

    return 0;
}
