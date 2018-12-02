#include "keybind.h"

#include "awm.h"

#include <X11/Xlib.h>

void setup_keybinds(awm_state *state){
    /* Rofi keybind */
    XGrabKey(state->disp,
	    XKeysymToKeycode(state->disp, XStringToKeysym("X")),
	    Mod1Mask,
	    state->root,
	    True,
	    GrabModeAsync,
	    GrabModeAsync);
    /* Exit keybind */
    XGrabKey(state->disp,
	    XKeysymToKeycode(state->disp, XStringToKeysym("E")),
	    Mod1Mask,
	    state->root,
	    True,
	    GrabModeAsync,
	    GrabModeAsync);
    /* Terminal keybind */
    XGrabKey(state->disp,
	    XKeysymToKeycode(state->disp, XStringToKeysym("Return")),
	    Mod1Mask,
	    state->root,
	    True,
	    GrabModeAsync,
	    GrabModeAsync);
    /* Resize keybind */
    XGrabKey(state->disp,
	    XKeysymToKeycode(state->disp, XStringToKeysym("R")),
	    Mod1Mask,
	    state->root,
	    True,
	    GrabModeAsync,
	    GrabModeAsync);
    /* Close Window keybind */
    XGrabKey(state->disp,
	    XKeysymToKeycode(state->disp, XStringToKeysym("Q")),
	    Mod1Mask,
	    state->root,
	    True,
	    GrabModeAsync,
	    GrabModeAsync);

    /* Move Window keybind */
    XGrabButton(state->disp, 1, Mod1Mask, state->root, True, ButtonPressMask,
	    GrabModeAsync, GrabModeAsync, None, None);
}
