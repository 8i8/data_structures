#include "ds_msg.h"
#include <stdlib.h>
#include <ctype.h>

/*
 * _place_at_front: helper function, put the input string at the beginning of
 * the message.
 */
void _place_at_front(char *store, char *message, int len_store, int len_message)
{
	char transfer[MAX_LENGTH];

	memcpy(transfer, store, len_store + 1);
	memcpy(store, message, len_message + 1);
	strcat(store, transfer);
}

/*
 * _write_to_string: Write the input string to the stored message.
 */
char *_ds_write_to_string(int reverse, char *store, char *message)
{
	int len_store, len_message;

	len_store = strlen(store);
	len_message = strlen(message);

	/* String order, the 4 is for the ellipsis if the string does not fit
	 * and one for a space between the phrases. */
	if (MAX_LENGTH - len_store > len_message + 5) {
		if (reverse)
			_place_at_front(store, message, len_store, len_message);
		else
			strcat(store, message);
	} else
		strcat(store, " ...");

	return store;
}

/*
 * DS_Message_set: Compile a message and store it for further handling.
 */
int _ds_message_set(char *message, char *input, va_list *va)
{
	char *head, *va_str;
	int va_num;
	double va_flo;
	unsigned int va_unum;
	size_t va_size_t;
	head = message;

	while (*input)
	{
		if (*input != '%') {
			*message++ = *input++;
			continue;
		}
		switch (*++input)
		{
			case 's':
				for (va_str = va_arg(*va, char *); *va_str; va_str++)
					*message++ = *va_str;
				break;
			case 'd':
				va_num = va_arg(*va, int);
				message += sprintf(message, "%d", va_num);
				break;
			case 'f':
				va_flo = va_arg(*va, double);
				message += sprintf(message, "%f", va_flo);
				break;
			case 'u':
				va_unum = va_arg(*va, unsigned int);
				message += sprintf(message, "%u", va_unum);
				break;
			case 'l':
				if (*(input+1) == 'u') {
					input++;
					va_size_t = va_arg(*va, size_t);
					message += sprintf(message, "%lu", va_size_t);
				} else if (!isspace(*(input+1)))
					input++;
				break;
			default:
				break;
		}
		input++;
	}
	*message = '\0';

	return message - head;
}

