#include "../tests/DS_Test_output.h"
#include <stdio.h>
#include <string.h>

#define LEN 54

static char output[LEN];
static char *pt_out;

/* 
 * This function relies on the void* that is being passed in containing a char*
 * in the first memory space of whatever is being sent.
 */
int DS_Out_print_node(void *node, void *tail)
{
	if (node == NULL)
		return -1;

	char *out;
	out = (char*)node;
	printf("%s%s", out, (char*)tail);

	return 0;
}

int DS_Out_store(void *node, void *n)
{
	if (node == NULL || n == NULL)
		return -1;

	char *out;
	out = (char*)node;

	if ((pt_out - output) < (int)(LEN - strlen(out)))
		pt_out += sprintf(pt_out, out, strlen(out));

	return 0;
}

void DS_Out_reset()
{
	pt_out = output;
}

char *DS_Out_get_string()
{
	return output;
}

