/*
 * This code uses the <time.h> header to time functions at the lowest system
 * level thus the highest resolution.
 *
 * typedef __clockid_t clockid_t;
 * extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __THROW;
 *
 * https://linux.die.net/man/3/clock_getres
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/clock_gettime.html
 * https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html
 */
/*
 * CLOCK_MONOTONIC time is the total time.
 * CLOCK_MONOTONIC_RAW is Monotonic system-wide clock, not adjusted for
 * frequency scaling.
 * CLOCK_PROCESS_CPUTIME_ID is the time for the individual process.
 *
 * CLOCK_MONOTONIC
 * CLOCK_MONOTONIC_RAW
 * CLOCK_PROCESS_CPUTIME_ID
 */
#include <time.h>
#include <limits.h>
#include <float.h>
#include <data/DS_timer.h>

#define CLOCK_METHOD CLOCK_PROCESS_CPUTIME_ID

struct timespec start, end;

void time_start()
{
	clock_gettime(CLOCK_METHOD, &start);

	// Time this ...
}

double time_stop()
{
	double micro;

	// ... stop

	clock_gettime(CLOCK_METHOD, &end);
	micro = (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

	if (micro < DBL_EPSILON)
		return 0;

	return micro *= 0.000000001;
}

void time_loop()
{
	int i;
	time_start();

	for (i = 0; i < 10000; )
		i++;

	time_stop();
}

