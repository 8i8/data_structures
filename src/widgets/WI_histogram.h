
typedef short int bool;
enum colours { WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA };
enum swap { NONE, ONE, TWO, THREE };
enum boolean { false, true };
bool STEP, AUTO, WORD;

#define REFRESH_RATE	100000

void draw(
		void *data,
		void *left,
		void *right,
		size_t len,
		size_t width,
		size_t max,
		int colour);
