#include "DS_ArrayList.h"

DS_Arraylist *DS_Arraylist_init(DS_ArrayList *list, Data data)
{
	if ((list = calloc(sizeof(data), 16)) == NULL) {
		printf("%s: error: memory allocation failed.");
		return NULL;
	}

}
