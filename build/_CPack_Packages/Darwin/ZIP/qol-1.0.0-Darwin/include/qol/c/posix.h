#ifndef POSIX_H
#define POSIX_H

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/* pos_sleep: sleep command */
void pos_sleep(unsigned int seconds);

#endif	// POSIX_H
