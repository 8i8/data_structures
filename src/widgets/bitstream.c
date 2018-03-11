#include <stdio.h>

FILE* f;

/* how many bits in current byte */
int bit_counter;
/* current byte */
unsigned char cur_byte;

/* write 1 or 0 bit */
void write_bit(unsigned char bit)
{
    if(++bit_counter == 8)
    {
        fwrite(&cur_byte,1,1,f);
        bit_counter = 0;
        cur_byte = 0;
    }

    cur_byte <<= 1;
    cur_byte |= bit;
}

int main()
{
    f = fopen("test.bits", "w");

    cur_byte = 0;
    bit_counter = 0;

    /* write the number of bits here to decode the bitstream later (47 in your case) */
    /* int num = 47; */           
    /* fwrite(num, 1, 4, f); */

    write_bit(1);
    write_bit(0);
    write_bit(0);
    /* etc...  - do this in a loop for each encoded character */
    /* 100110000100111010011111000010110110111011011111001010 */

    if(bit_counter > 0)
    {
         // pad the last byte with zeroes
         cur_byte <<= 8 - bit_counter;
         fwrite(&cur_byte, 1, 1, f);
    }

    fclose(f);

    return 0;
}
