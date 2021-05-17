#ifndef DS_TEST
#define DS_TEST
/*
 * This Data struct is the default data type used in the data structure test
 * suit, the idea here is that it can be overridden when in standard uses and
 * any struct be passed through the code, but is required when running tests on
 * the suite.
 */
#include <stdio.h>

typedef struct Data {
	char str[16];
	size_t num;
} Data;

/*
 * This struct is used in arrays of structs that have one contiguous memory
 * location.
 */
typedef struct {
	size_t len;
	size_t num;
	size_t num2;
	char str[];
} Test;

#endif
