#include <stdio.h>

int (*test_ptr)(const char *restrict);

// deriveted type : posix -> 數值可有限操作
// pid_t fork(void)
// 不用int 因為可能和32 bit machine or 64-bit machine
// ++++++i++++++ : ub : undefined behavior : C 語言很多
typedef int (*func_t)(const char * restrict);



int printf_internal(int a ,int b)
{
	printf("symbol %d \n",a+b);
}

// C 全部都是純量
// c89 才出現 
//   posix 是為了給一大堆人開發unix 制定的標準用低(ex 大同電鍋
// void *p 合法
// void p 不合法
// C 語言是重點是數值 不是指標

// * value of
// & address of

int main()
{
	printf_internal(7,9);
	void *x = printf;
	test_ptr=x;
	printf("%x %x %x\n",test_ptr,*test_ptr,**test_ptr);
	(*test_ptr)("Hello\n");
	(*printf)("Hello is legal\n");
	(********************************printf)("Hello is legal **************\n");
	(* (func_t) x)("Hello \n");
	//	(*x)("Hello \n"); // compiler error
	// 何謂轉型意義？？
	// 1.不論任何東西都是數值
	// 2.數值如何使用 完全依據他的型態<=> C 語言操作於型態


	/*6.2.5 好好解釋它 語言規格書
	 * %x 其實就是轉型了, C為了避免不正確的轉型
	*/
	int arr[10]; /* (int arr[]) ==  (int *arr)*/
	printf("%x %x %x",arr,*arr,&arr);
	printf("%x %x %x\n",test_ptr,*test_ptr,**test_ptr);

	// lvalue C11  *(int32_t * const) (0x67a9) = 0xaa6;


	return 0;
}
