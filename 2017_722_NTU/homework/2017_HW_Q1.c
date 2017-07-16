#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*
*  output bit-reverse result
*    @IN:  input unsigned integer
*    @OUT: output bit reverse result
*    reference: http://acm.nudt.edu.cn/~twcourse/BitwiseOperation.html
*/
uint32_t Q1(uint32_t x)
{
    uint32_t n = x;
    n = ((n & 0xffff0000) >> 16) | ((n & 0x0000ffff) << 16);
    n = ((n & 0xff00ff00) >>  8) | ((n & 0x00ff00ff) <<  8);
    n = ((n & 0xf0f0f0f0) >>  4) | ((n & 0x0f0f0f0f) <<  4);
    n = ((n & 0xcccccccc) >>  2) | ((n & 0x33333333) <<  2);
    n = ((n & 0xaaaaaaaa) >>  1) | ((n & 0x55555555) <<  1);
    return n;
}

// samle for homework 1
uint16_t Q1_reversebit_WhileVersion(uint16_t x)
{
	uint8_t count=0;
	uint16_t output = 0;
	for(count=0;count<16;count++)
	{
		if((x & (0x01 << count)))
			output |= (0x01 << (15 - count));
			//output |= (0x01 << (count));
			//output |= (X1 << (16 - count));
	}

	return output;
}

void show_binary(uint32_t n,size_t size)
{
	int i;
	for(i=0; i<size; i++)
		if(n & (0x8000>>i))
			printf("1");
		else
			printf("0");
	puts("");
}

int main()
{
	int i;
	i = 0;
	while( i < 16)
	{
		//uint32_t a = 0x00000000 | (0x00000001<<i++);
		uint16_t a = 0x0 | (0x01<<i++);
		printf("step %u %u %u\n",i ,a , Q1(a));
		printf("ori ");
		show_binary(a,16);
		printf("after ");
		show_binary(Q1_reversebit_WhileVersion(a),16);
		printf("===========\n\n");
	}
}
