#include "GE_error.h"
#include "GE_msg.h"

static char error[MAX_LENGTH + 1];
static char store[MAX_LENGTH + 1];
static char send[MAX_LENGTH + 1];
static int state = 0;

/*
 * DS_error_set: Erase any existing message and set a new message in its
 * place.
 */
void DS_error_set(char *input, ...)
{
	store[0] = '\0';
	va_list va;
	va_start(va, input);
	if(ds_message_set(error, input, &va))
		state = 1;
	va_end(va);

	ds_write_to_string(0, store, error);
}

/*
 * DS_error_append: Append to the current message.
 */
void DS_error_append(char *input, ...)
{
	va_list va;
	va_start(va, input);
	ds_message_set(error, input, &va);
	va_end(va);

	ds_write_to_string(0, store, " ");
	ds_write_to_string(0, store, error);
	state = 1;
}

/*
 * DS_error_insert: Insert at the beginning of the current message.
 */
void DS_error_insert(char *input, ...)
{
	va_list va;
	va_start(va, input);
	ds_message_set(error, input, &va);
	va_end(va);

	ds_write_to_string(1, store, " ");
	ds_write_to_string(1, store, error);
	state = 1;
}

/*
 * DS_error_get: Return message and reset to empty.
 */
char *DS_error_get(void)
{
	strcpy(send, store);
	store[0] = '\0';
	state = 0;

	return send;
}

/*
 * DS_error_print: Write message to terminal and reset.
 */
void DS_error_print(void)
{
	ds_write_to_string(1, store, "error: ");
	strcpy(send, store);
	store[0] = '\0';
	state = 0;
#ifdef __unix__
	write(1, send, strlen(send));
#endif
#ifndef __unix__
	printf("%s", send);
#endif
}

/*
 * DS_error_state: Returns the status of the message service, 0 as all clear, 1
 * if an message is pending.
 */
int DS_error_state(void)
{
	return state;
}

/*
 * DS_error_reset: Set to empty, with no message.
 */
void DS_error_reset(void)
{
	store[0] = '\0';
	state = 0;
}
