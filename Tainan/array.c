#include <stdio.h>

// where life cycle ? It's important
char *str()
{
	char p[]="hello world\n";
	return p; // segment fault
}

{
// multi thread problem ??
char *ptr
if(ptr)
	free(ptr);
}


int main()
{
	char a[10]={0};
	a[3]=5;
	// C 連續記憶體 1234567890
	printf("%p %p ",&a,a);
	printf("%d %d %d %c \n",a[3],3[a],*(a+3),"1234567890"[3]); // string iteratir
	printf("%d %d %d %c \n",a[3],3[a],*(a+3),"1234567890"[1]); // string iteratir
	
	// itoa 123456789
	// b_printfhex


	printf("%s",str());
}
