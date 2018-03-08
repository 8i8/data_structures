#include "DS_Test_output.h"
#include <stdio.h>
#include <string.h>

#define LEN 54


static char output[LEN];
static char *pt_out;

/* This function relies on the void* that is being passed in containing a char*
 * in the first place of what ever it may be. */
int print(void *list, char *tail)
{
	if (list == NULL)
		return -1;

	char *out;
	out = (char*)list;
	printf("%s%s", out, tail);

	return 0;
}

int print_n(void *list, void *n)
{
	if (list == NULL || n == NULL)
		return -1;

	char *out;
	out = (char*)list;

	if ((pt_out - output) < (int)(LEN - strlen(out)))
		pt_out += sprintf(pt_out, out, strlen(out));

	return 0;
}

void reset_output()
{
	pt_out = output;
}

char *get_output()
{
	return output;
}
