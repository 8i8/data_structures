#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

/* DS_error_set: Erase any existing message and set a new message in its
 * place */
void DS_error_set(char *input, ...);

/* DS_error_append: Append to the current message */
void DS_error_append(char *input, ...);

/* DS_error_insert: Insert at the beginning of the current message */
void DS_error_insert(char *input, ...);

/* DS_error_get: Return message and reset to empty  */
char *DS_error_get(void);

/* DS_error_print: Write message to terminal and reset */
void DS_error_print(void);

/* DS_error_state: Returns the status of the message service, 0 as all clear, 1
 * if an message is pending */
int DS_error_state(void);

/* DS_error_reset: Set to empty, with no message  */
void DS_error_reset(void);

