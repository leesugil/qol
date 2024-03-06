#ifndef _CLOCK_H
#define _CLOCK_H

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

struct timeval start_wall, end_wall;
double elapsed_time;
clock_t start_cpu, end_cpu;
double cpu_time_used;

void sclock_start(char *prog)
{
	fprintf(stderr, "\n%s\t*** START OF CODE ***\n\n", prog);
	
	/* wall-clock time */
	extern struct timeval start_wall;

	gettimeofday(&start_wall, NULL);

	/* cpu time */
	extern clock_t start_cpu;

	start_cpu = clock();
}

void clock_start(void)
{
	sclock_start("");
}

void sclock_end(char *prog)
{
	/* collect cpu time */
	extern clock_t start_cpu, end_cpu;
	extern double cpu_time_used;
	
	end_cpu = clock();
	cpu_time_used = ((double) (end_cpu - start_cpu)) / CLOCKS_PER_SEC;
	fprintf(stderr, "\n\n%s\t*** END OF CODE ***\n\tCPU time used: %f seconds\n", prog, cpu_time_used);

	/* collect wall-clock time */
	extern struct timeval start_wall, end_wall;
	extern double elapsed_time;

	gettimeofday(&end_wall, NULL);
	elapsed_time = (end_wall.tv_sec - start_wall.tv_sec) + (end_wall.tv_usec - start_wall.tv_usec) / 1000000.0;
	fprintf(stderr, "\n%s\tElapsed wall-clock time: %f seconds\n", prog, elapsed_time);
}

void clock_end(void)
{
	sclock_end("");
}

#endif	/* _CLOCK_H */
