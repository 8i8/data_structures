#include <data/DS_message.h>
#include <data/ds_msg.h>

static char message[MAX_LENGTH + 1];
static char store[MAX_LENGTH + 1];
static char send[MAX_LENGTH + 1];
static int state = 0;

/*
 * DS_message_set: Erase any existing message and set a new message in its
 * place.
 */
void DS_message_set(char *input, ...)
{
	store[0] = '\0';
	va_list va;
	va_start(va, input);
	if(_ds_message_set(message, input, &va))
		state = 1;
	va_end(va);

	_ds_write_to_string(0, store, message);
}

/*
 * DS_message_append: Append to the current message.
 */
void DS_message_append(char *input, ...)
{
	va_list va;
	va_start(va, input);
	_ds_message_set(message, input, &va);
	va_end(va);

	_ds_write_to_string(0, store, " ");
	_ds_write_to_string(0, store, message);
	state = 1;
}

/*
 * DS_message_insert: Insert at the beginning of the current message.
 */
void DS_message_insert(char *input, ...)
{
	va_list va;
	va_start(va, input);
	_ds_message_set(message, input, &va);
	va_end(va);

	_ds_write_to_string(1, store, " ");
	_ds_write_to_string(1, store, message);
	state = 1;
}

/*
 * DS_message_get: Return message and reset to empty.
 */
char *DS_message_get(void)
{
	strcpy(send, store);
	store[0] = '\0';
	state = 0;

	return send;
}

/*
 * DS_message_print: Write message to terminal and reset.
 */
void DS_message_print(void)
{
	_ds_write_to_string(1, store, "info: ");
	strcpy(send, store);
	store[0] = '\0';
	state = 0;
#ifdef _unix_
	write(1, send, strlen(send));
#endif
#ifndef _unix_
	printf("%s", send);
#endif
}

/*
 * DS_message_state: Returns the status of the message service, 0 as all clear, 1
 * if an message is pending.
 */
int DS_message_state(void)
{
	return state;
}

/*
 * DS_message_reset: Set to empty, no message.
 */
void DS_message_reset(void)
{
	store[0] = '\0';
	state = 0;
}
