#include <stdio.h>

int B=2;

void func(int **p)
{
	*p=&B;
}

//void func1(int *p)
//{
//	p=&B;
//}


int main(){

	int A=1,C=3;
	int *ptrA = &A;
	func(&ptrA);
	//func(ptrA);  // ptr to ptr
	printf("%d",*ptrA);
	return 0;
}
