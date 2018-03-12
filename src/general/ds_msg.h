#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 4096

/* DS_Message_set: Compile a message and store it for further handling */
int _ds_message_set(char *message, char *input, va_list *va);

/* _write_to_string: Write the input string to the stored message. */
char *_ds_write_to_string(int reverse, char *input, char *message);
