/*
 * This Data struct is the default data type used in the data structure test
 * suit, the idea here is that it can be overridden when in standard uses and
 * any struct be passed through the code, but is required when running tests on
 * the suite.
 */
#include <stdio.h>

#ifndef _data_h
#define _data_h
typedef struct Data {
	char str[255];
	size_t len;
} Data;
#endif

