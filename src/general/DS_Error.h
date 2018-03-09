#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

/* DS_Error_set: Erase any existing message and set a new message in its
 * place */
void DS_Error_set(char *string, ...);

/* DS_Error_append: Append to the current message */
void DS_Error_append(char *string, ...);

/* DS_Error_insert: Insert at the beginning of the current message */
void DS_Error_insert(char *string, ...);

/* DS_Error_get: Return message and reset to empty */
char *DS_Error_get(void);

/* DS_Error_state: Returns the status of the message service, 0 as all clear, 1
 * if an message is pending */
int DS_Error_state(void);

