#include <stdarg.h>

/* DS_message_set: Compile a message and store it for handling */
void DS_message_set(char *string, ...);
void DS_message_append(char *string, ...);
void DS_message_insert(char *string, ...);

/* DS_message_print: Print message string and reset to empty string. */
char *DS_message_get(void);

/* DS_message_print: Write message to terminal and reset */
void DS_message_print(void);

/* DS_message_state: Returns the status of the message service, 0 as all clear, 1
 * if an message is pending. */
int DS_message_state(void);

/* DS_message_reset: Set to empty, with no message  */
void DS_message_reset(void);

