#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

/* jyError_get:    Print error string and reset to empty string */
char *jyError_print(void);

/* jyError_get:    Returns error string */
char *jyError_get(void);

/* jyError_set:    Prevent to start of error string */
void jyError_set(uint_fast8_t reverse, char *string, ...);

/* jyError_state: Returns the stattus of the error service, 0 as all clear, 1
 * if an error is pending  */
int jyError_state(void);
