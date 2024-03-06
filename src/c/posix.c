#include "qol/c/posix.h"

void pos_sleep(unsigned int seconds)
{
	#ifdef _WIN32
	Sleep(seconds * 1000);
	#else
	sleep(seconds);
	#endif
}
