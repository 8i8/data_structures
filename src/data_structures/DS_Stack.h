
typedef struct _stack {
	void *elems;
	int elem_size;
	int log_length;
	int alloc_length;
} Stack;

void DS_Stack_new(Stack *s, int elem_size);
void DS_Stack_dispose(Stack *s);
void DS_Stack_push(Stack *s, void *elem_addr);
void DS_Stack_pop(Stack *s, void *elem_addr);
