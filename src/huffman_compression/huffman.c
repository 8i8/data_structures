#include <stdio.h>
#include "char_frequency.h"

int main(int argc, char *argv[])
{
	FILE *fp;
	DS_LinkedList *list = NULL;

	while (--argc)
		if ((fp = fopen(*++argv, "r")) == NULL)
			printf("Can not open '%s'.\n", argv[argc+1]);

	frequency_map(&list, fp);
	print_frequency(&list);
	DS_LinkedList_clear(&list);

	return 0;
}

