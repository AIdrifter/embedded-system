#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <time.h>

int clz_rather_add(unsigned int x)
{
    if (x == 0) return 32;
    int n = 0;
    //0000 0000 0001 1111 1111 1111 1111 1111
    //0000 0000 0000 0000 1111 1111 1111 1111
    if (x <= 0x0000FFFF) { n += 16; x <<= 16; }

    //0000 0000 0001 1111 1111 1111 1111 1111
    //0000 0000 1111 1111 1111 1111 1111 1111
    if (x <= 0x00FFFFFF) { n += 8; x <<= 8; }

    //0000 0001 1111 1111 1111 1111 1111 1111
    //0000 1111 1111 1111 1111 1111 1111 1111
    if (x <= 0x0FFFFFFF) { n += 4; x <<= 4; }


    //0000 0111 1111 1111 1111 1111 1111 1111
    //0011 1111 1111 1111 1111 1111 1111 1111
    if (x <= 0x3FFFFFFF) { n += 2; x <<= 2; }


    //0000 1111 1111 1111 1111 1111 1111 1111
    //0111 1111 1111 1111 1111 1111 1111 1111
    if (x <= 0x7FFFFFFF) { n += 1; x <<= 1; }
    return n+1;
}

int clz_mask_add(unsigned int x)
{
    if (x == 0) return 32;
    int n = 0;
    if (x & 0x0000FFFF) { n += 16; x <<= 16; }
    if (x & 0x00FFFFFF) { n += 8; x <<= 8; }
    if (x & 0x0FFFFFFF) { n += 4; x <<= 4; }
    if (x & 0x3FFFFFFF) { n += 2; x <<= 2; }
    if (x & 0x7FFFFFFF) { n += 1; x <<= 1; }
    return n;
}


int clz_mask_sub(unsigned int x)
{
  if (!x) return 32;
  int e = 31;
  //1111 1111 1111 1111 0000 0000 0000 0000
  if (x&0xFFFF0000)   { e -=16; x >>=16; }
  //0000 0000 0000 0000 1111 1111 0000 0000
  if (x&0x0000FF00)   { e -= 8; x >>= 8; }
  //0000 0000 0000 0000 0000 0000 1111 0000
  if (x&0x000000F0)   { e -= 4; x >>= 4; }
  //0000 0000 0000 0000 0000 0000 0000 1100
  if (x&0x0000000C)   { e -= 2; x >>= 2; }
  //0000 0000 0000 0000 0000 0000 0000 0010
  if (x&0x00000002)   { e -= 1; }
  return e;
}

int clz_iteration(uint32_t x) {
    int n = 32, c = 16;
    do {
        uint32_t y = x >> c;
        if (y) { n -= c; x = y; }
        c >>= 1;
    } while (c);
    return (n - x);
}

// gcc -O0 : disable compiler optimizied
int main()
{
	// init random seed
	srand (time(NULL));
	uint32_t i;
	uint32_t number = UINT_MAX;
	uint32_t R = rand()%UINT_MAX;

	uint32_t (*f_ptr)();
	for (i=0;i<number;i++)
	{
		R=rand()%UINT_MAX;
		clz_iteration(R);
	}

}

