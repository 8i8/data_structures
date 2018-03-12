#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Binary display
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static unsigned len = 16;
static char *ptr, *stack;

void _expand_buffer()
{
	int pos;
	len <<= 1;
	assert(len);
	pos = ptr - stack;
	stack = realloc(stack, len + 1 );
	ptr = stack + pos;
}

void _write_word(unsigned in)
{
	*ptr++ = in + '0';
	*ptr = '\0';
	
	if (ptr - stack >= len)
		_expand_buffer();
}

/*
 * print_binary: Print the binary representation of an integer.
 */
unsigned _print_binary(unsigned n, unsigned len)
{
	if (n < 2) {
		_write_word(n);
	} else if (n > 1) {
		len = _print_binary(n / 2, (len) ? len - 1 : 0);
		_write_word(n % 2);
	}
	return len;
}

/*
 * W_Print_binary: Displays a binary representation of the given integer, the
 * width argument denotes the number of bits to be displayed after the most
 * significant bit, including that which denotes the requested integer.
 */
void W_Print_binary(unsigned n, unsigned width)
{
	stack = ptr = malloc(len + 1);
	width = _print_binary(n, width);
	if (width > 1)
		while (width)
			putchar('0'), width--;
	printf("%s", stack);
	free(stack);
} 

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Bitwise operations
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/*
 * getbits: Returns the right adjusted n-bit field of x that begins at
 * position p, position 0 is the least significant bit of the word.
 */
unsigned getbits(unsigned x, unsigned p, unsigned n)
{
	return (x >> (p+1-n)) & ~(~(unsigned)0 << n);
}

