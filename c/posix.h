#ifndef POSIX_H
#define POSIX_H

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void pos_sleep(unsigned int seconds)
{
	#ifdef _WIN32
	Sleep(seconds * 1000);
	#else
	sleep(seconds);
	#endif
}


#endif	// POSIX_H
