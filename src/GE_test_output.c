#include <data/DS_test_output.h>
#include <stdio.h>
#include <string.h>

#define LEN 54

static char output[LEN];
static char msg[LEN];
static char *pt_msg;

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

	char **out;
	out = (char**)node;

	if ((pt_msg - msg) < (int)(LEN - strlen(*out)))
		pt_msg += sprintf(pt_msg, *out, strlen(*out));

	return 0;
}

void DS_Out_reset()
{
	pt_msg = msg;
	*pt_msg = '\0';
}

char *DS_Out_msg()
{
	memcpy(output, msg, LEN);
	pt_msg = msg;
	*pt_msg = '\0';
	return output;
}

