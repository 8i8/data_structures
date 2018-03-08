#include "../general/DS_Error.h"

#define MAX_LENGTH 4096

static char error[MAX_LENGTH];
static char send[MAX_LENGTH];
static int state = 0;

/*
 * DS_Error_set: Compile an error message as it occurs and store it for error
 * handling.
 */
void DS_Error_set(uint_fast8_t reverse, char *string, ...)
{
	char transfer[MAX_LENGTH];
	char input[MAX_LENGTH];
	char *pt, *sval, *in;
	va_list va;
	int len_in, len_er, ival;
	static uint_fast8_t mark = 0;
	in = input;
	len_in = len_er = 0;

	va_start(va, string);
	for (pt = string; *pt; pt++) {
		if (*pt != '%') {
			*in++ = *pt;
			continue;
		}
		switch (*++pt) {
		case 's':
			for (sval = va_arg(va, char *); *sval; sval++)
				*in++ = *sval;
			break;
		case 'd':
			ival = va_arg(va, int);
			in += sprintf(in, "%d", ival);
			break;
		default:
			break;
		}
	}
	*in = '\0';
	va_end(va);

	len_in = strlen(input);
	len_er = strlen(error);

	if (!reverse && MAX_LENGTH - len_er > len_in) {
		sprintf(transfer, error);
		sprintf(error, input);
		strcat(error, transfer);
	} else if (reverse && MAX_LENGTH - len_er > len_in)
		strcat(error, input);
	else if (!mark && MAX_LENGTH - 4 > len_in) {
		strcat(error, " ...");
		mark++;
	}
	state = -1;
}

/*
 * jyError_get:    Returns error string.
 */
char *DS_Error_get(void)
{
	return error;
}

/*
 * jyError_get:    Print error string and reset to empty string.
 */
char *DS_Error_print(void)
{
	sprintf(send, error);
	error[0] = '\0';
	state = 0;

	return send;
}

/*
 * jyError_state: Returns the status of the error service, 0 as all clear, 1
 * if an error is pending.
 */
int DS_Error_state(void)
{
	return state;
}

