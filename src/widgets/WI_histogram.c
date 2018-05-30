#include <stdio.h>
#include <unistd.h>
#include "../tests/DS_Struct.h"
#include "WI_histogram.h"

/*
 * Clear the screen.
 */
void clearScreen()
{
	puts("\033[H\033[J");
}

/*
 * Print out an array of int's.
 */
void pArray(void *data, size_t len, size_t width)
{
	size_t i;
	char *v = data;

	for (i = 0; i <= len; i++)
		printf("\033[37m%2lu ", ((Test*)(v+i * width))->num2);
	putchar('\n');
	for (i = 0; i <= len; i++)
		printf("\033[37m%2lu ", i);
	putchar('\n');
}

/*
 * Generate and print a histogram of an array of integers.
 */
void histogram(void *data, size_t len, size_t width, size_t max, void *left, void *right, int colour)
{
	char *v, *l, *r;
        v = data, l = left, r = right;
	int hist[len+1][max+1];
	size_t i, j;

	for (i = 0; i <= len; i++) {
		for (j = 0; j < max; j++)
			if (j < ((Test*)(v + i * width))->num2)
				hist[i][j] = '|';
			else
				hist[i][j] = ' ';
	}

	for (i = max; i > 0; i--) {
		for (j = 0; j <= len; j++) {
			if (j == ((Test*)l)->num || j == ((Test*)r)->num) {
				if (colour == RED)
					printf(" \033[1;31m%c ", hist[j][i-1]);
				else if (colour == GREEN)
					printf(" \033[1;32m%c ", hist[j][i-1]);
				else if (colour == YELLOW)
					printf(" \033[1;33m%c ", hist[j][i-1]);
				else if (colour == BLUE)
					printf(" \033[1;34m%c ", hist[j][i-1]);
				else if (colour == MAGENTA)
					printf(" \033[1;35m%c ", hist[j][i-1]);
			} else
				printf(" \033[37m%c ", hist[j][i-1]);
		}
		printf("\n");
	}
}

void draw(
		void *data, void *left, void *right,
		size_t len, size_t width, size_t max,
		int colour)
{
	char *sw, c;
	Test *l, *r;
        l = left, r = right;

	clearScreen();
	histogram(data, len, width, max, left, right, colour);
	pArray(data, len, width);
	if (WORD)
		printf("\033[37mleft: v[%lu]=%lu,\tright v[%lu]=%lu\n",
				l->num, l->num2, r->num, r->num2);

	if (STEP) {
	//if (STEP && ((colour == RED && l->num2 > r->num2) || colour == YELLOW)) {
		if ((c = getchar()) == 's')
			STEP = false;
	} else
		usleep(REFRESH_RATE);
}

