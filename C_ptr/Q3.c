#include <stdio.h>
#include <stdlib.h>

// gcc risk.c -funsigned-char
// signed or unsigned ??<----------default is compiler decide
int tmp = 10000; //UNIT_MAX
int main(){
	//
	// 10000 ->  '0x2710' 
	// answer is 16
	char *p = (char*)&tmp;
	printf("%d",*p);
}
