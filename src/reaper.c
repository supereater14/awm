#include "reaper.h"

#include <signal.h>
#include <stddef.h>
#include <sys/wait.h>

void reaper(int sig){
    /* Make sure we actually need to reap */
    if(sig != SIGCHLD){
	return;
    }

    /* Reap the child */
    wait(NULL);
}

int setup_reaper(){
    struct sigaction reaper_action;

    /* Setup action */
    reaper_action.sa_handler = reaper;
    sigemptyset(&reaper_action.sa_mask);
    reaper_action.sa_flags = 0x0;

    /* Set action handler */
    return sigaction(SIGCHLD, &reaper_action, NULL);
}
