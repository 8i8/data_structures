
typedef struct stack {
	void *elems;
	int elem_size;
	int log_length;
	int alloc_length;
} Stack;

void DS_stack_new(Stack *s, int elem_size);
void DS_stack_dispose(Stack *s);
void DS_stack_push(Stack *s, void *elem_addr);
void DS_stack_pop(Stack *s, void *elem_addr);
