#ifndef _data_h
#define _data_h
typedef struct Data {
	char *string;
	int len;
} Data;
#endif

typedef struct dS_ArrayList {
	struct dS_ArrayList *next;
	Data data;
} dS_ArrayList;
