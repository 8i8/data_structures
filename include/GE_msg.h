#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 4096

/* ds_message_set: Compile a message and store it for further handling */
int ds_message_set(char *message, char *input, va_list *va);

/* write_to_string: Write the input string to the stored message. */
char *ds_write_to_string(int reverse, char *input, char *message);

/* ds_check_messages: INternal function to call both the message and the error
 * service, reseting both when done; A clean way to insure that this is done at
 * the end of every function in the test suit. */
void ds_check_messages(int msg, int err);

