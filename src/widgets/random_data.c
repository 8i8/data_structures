#include <time.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Return a random value between the given limits, I have used timespec to
 * generate the seed for my random value, for this reason the program will only
 * run on a POSIX machine, I shall look further into this subject in the future
 * as it is clearly a facinating area of the computing landscape.
 *
 * <time.h>
 *
 * typedef __clockid_t clockid_t;
 * extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __THROW;
 *
 * https://linux.die.net/man/3/clock_getres
 * http://pubs.opengroup.org/onlinepubs/9699919799/functions/clock_gettime.html
 * https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html
 */

/*
 * WI_seed_rand: Seed random sequance,
 */
void WI_seed_rand(void)
{
	struct timespec seed;
	clock_gettime(CLOCK_MONOTONIC, &seed);
	srand(seed.tv_nsec);
}

/*
 * WI_rand: Return a random number in the given range.
 */
int WI_rand(int range)
{
	return rand()%range+1;
}

/*
 * WI_gen_char: Returns a random char.
 */
char WI_gen_char(void)
{
	return rand()%26 + 'a';
}

/*
 * WI_gen_word: Returns a random string of char of the given length.
 */
char *WI_gen_word(char *str, size_t len)
{
	size_t i;
	char* ptr;
	ptr = str;

	for (i = 0; i < len-1; i++)
		*ptr++ = WI_gen_char();
	*ptr++ = ' ';

	return ptr;
}

int _word_len(size_t len)
{
	assert(len > 0);
	return rand() % ((len > 15) ? 15 : len) + 1;
}

/*
 * WI_gen_sentance: Returns a null terminated random sentance with a maximum
 * length of len - 1.
 */
char *WI_gen_sentance(char *str, size_t len)
{
	size_t w_len, i;
	char *ptr;
	ptr = str;

	for (i = 0; i < len && (((w_len = _word_len(len - i)) + i) < len); i += w_len)
		if (w_len)
			ptr = WI_gen_word(ptr, w_len);

	while (*(ptr-1) == ' ')
		--ptr;

	if (ptr != str)
		*ptr++ = '.';

	*ptr = '\0';

	return str;
}

