#include <stdio.h>


int add(int a, int b)
{
    if (b == 0)
		return a;
    int sum = a ^ b; // 相加但不進位
    int carry = (a & b) << 1; // 進位但不相加
    return add(sum, carry);
}


int mul(int a, int b)
{

}


int main()
{
	printf("add %d \n",add(4,5));
}
