/*
 * This Data struct is the default data type used in the data structure test
 * suit, the idea here is that it can be overridden when in standard uses and
 * any struct be passed through the code, but is required when running tests on
 * the suite.
 */
#include <stdio.h>

#ifndef data_
#define data_
typedef struct Data {
	char str[16];
	size_t num;
} Data;
#endif

/*
 * This struct is used in arrays of structs that have one contiguous memory
 * location.
 */
#ifndef test_
#define test_
typedef struct {
	size_t len;
	size_t num;
	size_t num2;
	char str[];
} Test;
#endif

