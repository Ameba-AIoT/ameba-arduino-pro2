#include <stdlib.h>
#include <time.h>

/* fill random number to buffer */
int getentropy(void *buffer, size_t length)
{
	int *buf = (int *)buffer;
	srand(time(NULL));

	for (int i = 0; i < length / 4; i++) {
		buf[i] = rand();
	}
	int rest = length % 4;
	if (rest) {
		char *bufc = (char *)&buf[length / 4];
		int tmp = rand();
		if (rest > 0)	{
			bufc[0] = (char)(tmp >> 0 & 0xff);
		}
		if (rest > 1)	{
			bufc[1] = (char)(tmp >> 8 & 0xff);
		}
		if (rest > 2)	{
			bufc[2] = (char)(tmp >> 16 & 0xff);
		}
	}

	return 0;
}