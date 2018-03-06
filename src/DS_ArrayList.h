#include "DS_Struct.h"
 
typedef struct dS_ArrayList {
	struct dS_ArrayList *next;
	Data data;
} dS_ArrayList;
