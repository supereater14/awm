#ifndef REAPER_H
#define REAPER_H

/* Reaps any children it finds */
void reaper(int sig);

/* Sets up the reaper to wait on incoming signals */
int setup_reaper();

#endif
