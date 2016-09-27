#include <stdio.h>

int B = 2;
void func(int **p) { *p = &B; printf("address of B %p\n",&B); }

int main()
{
	// *ptrA` 的數值從 1 變成 2，而且 ptrA 指向的物件也改變了
	// we hope ptrA saved address of global varaible B
    int A = 1, C = 3;
    int *ptrA = &A;
    printf("before ptrA  %p\n",ptrA);
    func(&ptrA);
    printf("after ptrA  %p \n",ptrA);
    printf("*ptrA %d \n", *ptrA);
    return 0;
}
