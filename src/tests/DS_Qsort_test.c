#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "../tests/DS_Struct.h"
#include "../data_structures/DS_Qsort.h"
#include "../general/DS_Error.h"
#include "../widgets/random_data.h"

typedef int (*comp)(const void *, const void *);

int strscmp(const void* v1, const void* v2);
int intscmp(const void* v1, const void* v2);

#define WIDTH	1000	/* Maximum width of an object */
#define LEN	1000	/* Maximum number of objects */

void print_list(void *list, size_t len, size_t width);

size_t set_size(int range)
{
	return rand() % range+1;
}

void set_structs(void *list, size_t len, size_t width)
{
	size_t i, o_size;
	Test *obj = list;
	char *ptr;
	ptr = list;
	o_size = sizeof(Test);

	for (i = 0; i < len; i++) {
		assert(o_size < width);
		obj->len = width - o_size - 1;
		WI_gen_sentance(obj->str, obj->len);
		obj->num = i;
		obj->num2 = rand() % len + 1;
		ptr += width;
		obj = (Test*)ptr;
	}
}

int check_increment(void *list, size_t len, size_t width, comp fn)
{
	char *obj, *last;
	obj = list;
	size_t i;
	int t;

	for (i = 0; i < len; i++, obj += width) {
		if (i > 0) {
			t = fn (obj, last);
			if (t < 0) {
				printf("%s(): qsort error, sort failed.", __func__);
				return 1;
			}
		}
		last = obj;
	}
	return 0;
}

void DS_Qsort_test()
{
	size_t width, len, count;
	char* mem;
	Test *list;

	srand(time(NULL));

	count = 100;
	while (count--)
	{
		width = rand() % WIDTH + sizeof(Test);
		len = rand() % LEN + 1;
		mem = malloc(width * len);
		list = (Test*)mem;

		set_structs(mem, len, width);

		DS_Qsort(list, len, width, intscmp);
		if (check_increment(list, len, width, intscmp)) {
			printf("%s\n", DS_Error_get());
			free(mem);
			break;
		}

		free(mem);
	}
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  sort functions
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/*
 * strscmp: Wrapper for struct, strcmp sort function.
 */
int strscmp(const void* v1, const void* v2)
{
	const Test *s1, *s2;
	s1 = v1, s2 = v2;
	return strcmp((const void*)s1->str, (const void*)s2->str);
}

int intscmp(const void* v1, const void* v2)
{
	const Test *s1, *s2;
	s1 = v1, s2 = v2;
	return s1->num2 - s2->num2;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  print
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/*
 * print_list: Output to terminal.
 */
void print_list(void *l, size_t len, size_t width)
{
	size_t i;
	char* list = l;

	for (i = 0; i < len; i++) {
		printf("%10lu %10lu %s\n", ((Test*)(list+i * width))->num,
					((Test*)(list+i * width))->num2,
					((Test*)(list+i * width))->str);
	}
}

