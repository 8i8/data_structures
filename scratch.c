#include <stdio.h>
#include <stdlib.h>

typedef struct Data {
	int a;
	int b;
} Data;

int main(void)
{
	Data *data;

	data = malloc(sizeof(Data) *10);
	data[5].a = 12;

	printf("test %d", data[5].a);

	return 0;
}
