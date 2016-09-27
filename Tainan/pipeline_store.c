#include <stdio.h>
#include <stdlib.h>

int main()
{
	 int32_t a, b;
	 a=6; b=-7;
	 printf(" a = %d  b = %d \n",a,b);
	 printf(" a = %08x  b = %08x \n",a,b);
	 puts("");

	// if (b < 0) 
	//	a++;
	 //a -= b >> 31;
	 printf(" a = %08x  b = %08x b>>31 %08x \n",a,b,(b>>31));
	 a -= b >> 31;
	 printf(" a = %d  b = %d \n",a,b);
}
