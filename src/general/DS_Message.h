#include <stdarg.h>

/* DS_Message_set: Compile a message and store it for handling */
void DS_Message_set(char *string, ...);
void DS_Message_append(char *string, ...);
void DS_Message_insert(char *string, ...);

/* DS_Message_print: Print message string and reset to empty string. */
char *DS_Message_get(void);

/* DS_Message_state: Returns the status of the message service, 0 as all clear, 1
 * if an message is pending. */
int DS_Message_state(void);

