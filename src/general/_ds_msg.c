#include "_ds_msg.h"

/*
 * _place_at_front: helper function, put the input string at the beginning of
 * the message.
 */
void _place_at_front(char *input, char *message, int len_message, int len_input)
{
	char transfer[MAX_LENGTH];

	memcpy(transfer, message, len_message + 1);
	memcpy(message, input, len_input + 1);
	strcat(message, transfer);
}

/*
 * _write_to_string: Write the input string to the stored message.
 */
void _ds_write_to_string(int reverse, char *input, char *message)
{
	int len_input, len_message;

	len_input = strlen(input);
	len_message = strlen(message);

	/* String order, the 4 is for the ellipsis if the string does not fit
	 * and one for a space between the phrases. */
	if (MAX_LENGTH - len_message > len_input + 5) {
		if (reverse)
			strcat(strcat(message, " "), input);
		else
			_place_at_front(input, message, len_message, len_input);
	} else
		strcat(message, " ...");
}

/*
 * DS_Message_set: Compile a message and store it for further handling.
 */
int _ds_message_set(char *message, char *input, va_list va)
{
	char *head, *va_str;
	int va_num;
	head = message;

	while (*input)
	{
		if (*input != '%') {
			*message++ = *input;
			continue;
		}
		switch (*++input)
		{
			case 's':
				for (va_str = va_arg(va, char *); *va_str; va_str++)
					*message++ = *va_str;
				break;
			case 'd':
				va_num = va_arg(va, int);
				message += sprintf(message, "%d", va_num);
				break;
			default:
				break;
		}
		input++;
	}
	*message = '\0';

	return message - head;
}

