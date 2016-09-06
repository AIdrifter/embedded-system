#include <stdio.h>
#include <stdlib.h>

int add(int a,int b)
{
	if (b==0) return a;
	int sum = a^b;
	int carry=(a&b)<<1;
	return add(sum ,carry);
}

int mult(int a,int b)
{
	// static int sum = 0; // <----------bug here  life cycle <=> process cycle
	int sum = 0;
	if (b==0) return sum;
	sum=add(sum,a);
	return mult(a,b-1);
}

//  高手版
//  only support unsigned integer
//   小心算數位移(int) 邏輯位移(unsigned int)
int mul1(int a, int b)
{
    if (!a) {
        return 0;
    }
	// ~(b & 1) is better than b << 31 >>31 ??
	// The answer is not correct( find by yourself
    //return mul1(a << 1, b >> 1) + (a & (b << 31 >> 31));
    return mul1(a << 1, b >> 1) + (a & ( ~(b & 1)));
}

int main(){
	//# ./mul
	//# echo $?
	//return mul1(7,3);
	int a = 0x00000001;
	printf(" %08x %u\n",a,a);
	printf(" %08x %u\n",a&1,a&1);
	printf(" %08x %d\n ", ~(a&1),~(a&1));
	printf("[] %08x %d\n",a << 30, a<<30);
	printf(" %08x %d\n",a << 31, a<<31);
	printf(" %08x %d\n",a << 31 >> 31,a<<31>>31);

	return mul1(3,3);
	//return mult(mult(1,1),mult(1,1));
}
