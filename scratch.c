#include <stdio.h>
#include "src/DS_Timer.h"

int main(void)
{
	size_t i;
	double time = 0;
	i = 10000000;
	time_start();
	while (--i)
		;
	time = time_stop();

	printf("%f\n", time);

	return 0;
}
