#include <stdio.h>

FILE *fp;

int bit_counter;
unsigned char cur_byte;

void write_bit(unsigned char bit)
{
    if(++bit_counter == 8)
    {
        fwrite(&cur_byte, 1, 1, fp);
        bit_counter = 0;
        cur_byte = 0;
    }

    cur_byte <<= 1;
    cur_byte |= bit;
}

int main()
{
    fp = fopen("test.bits", "w");

    cur_byte = 0;
    bit_counter = 0;

    write_bit(1);
    write_bit(0);
    write_bit(0);

    /* Pad the last byte with 0's */
    if(bit_counter > 0) {
         cur_byte <<= 8 - bit_counter;
         fwrite(&cur_byte, 1, 1, fp);
    }

    fclose(fp);

    return 0;
}
