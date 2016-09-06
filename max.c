#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int sign(int32_t a) { return 1 ^ ((a >> 31) & 0x1); }
int max(int32_t a, int32_t b) { return a * sign(a - b) + b * (1 ^ sign(a - b)); }

int main()
{
	//int a = UINT_MAX;
	int a = INT_MAX -3;
	//int b = -9999;
	int b = -999999;
	printf(" %d ", max(a,b));
	return 0;
}
