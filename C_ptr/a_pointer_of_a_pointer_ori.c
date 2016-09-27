#include <stdio.h>

int B=2;

void func(int *p){
	*p=B;
}

int main(){
	int A=1,C=3;
	int *ptrA = &A;
	printf("=> %x\n",(unsigned int)ptrA);
	func(ptrA);
	printf("=> %x\n",ptrA);
	printf("%d\n",*ptrA);
	printf("%d\n",A);
	return 0;
}
