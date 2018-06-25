/* W_Print_binary: Displays a binary representation of the given integer, the
 * width argument denotes the number of bits to be displayed after the most
 * significant bit, including that which denotes the requested integer. */
void BI_Print_binary(int n, int width);

/* getbits: Returns the the right adjusted n-bit field of x that begins at
 * position p, position 0 is the least significalt bit of the word. */
unsigned BI_getbits(unsigned x, unsigned p, unsigned n);
