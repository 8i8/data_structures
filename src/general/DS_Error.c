#include "DS_Error.h"
#include "_ds_msg.h"

static char input[MAX_LENGTH + 1];
static char message[MAX_LENGTH + 1];
static char send[MAX_LENGTH + 1];
static int state = 0;

/*
 * DS_Error_set: Erase any existing message and set a new message in its
 * place.
 */
void DS_Error_set(char *string, ...)
{
	message[0] = '\0';

	va_list va;
	va_start(va, string);
	if (_ds_message_set(message, input, va))
		state = 1;
	va_end(va);

	_ds_write_to_string(0, message, input);
}

/*
 * DS_Error_append: Append to the current message.
 */
void DS_Error_append(char *string, ...)
{
	va_list va;
	va_start(va, string);
	if (_ds_message_set(message, input, va))
		state = 1;
	va_end(va);

	_ds_write_to_string(0, message, input);
}

/*
 * DS_Error_insert: Insert at the beginning of the current message.
 */
void DS_Error_insert(char *string, ...)
{
	va_list va;
	va_start(va, string);
	if (_ds_message_set(message, input, va))
		state = 1;
	va_end(va);

	_ds_write_to_string(1, message, input);
}

/*
 * DS_Error_get: Return message and reset to empty.
 */
char *DS_Error_get(void)
{
	sprintf(send, message);
	message[0] = '\0';
	state = 0;

	return send;
}

/*
 * DS_Error_state: Returns the status of the message service, 0 as all clear, 1
 * if an message is pending.
 */
int DS_Error_state(void)
{
	return state;
}

