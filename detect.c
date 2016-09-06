#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <limits.h>


#if LONG_MAX == 2147483647L
#define DETECT(X) (((X) - 0x01010101) & ~(X) & 0x80808080)
#else
#if LONG_MAX == 9223372036854775807L
#define DETECT(X) (((X) - 0x0101010101010101) & ~(X) & 0x8080808080808080)
#else
#error long int is not a 32bit or 64bit type.
#endif
#endif

int main(){
	long int a=100;
	
	//for ( a=; a+1; a < 0x)


	// used strlen
	//  detect null char
	// strlen source code
	// https://chromium.googlesource.com/native_client/nacl-newlib/+/old/master/newlib/libc/string/strchr.c
	// 對strlen 做最佳化
	DETECT(a);

	// http://www.java-tips.org/java-se-tips-100019/24-java-lang/1896-quick-sort-implementation-with-median-of-three-partitioning-and-cutoff-for-small-arrays.html
	// quick sort bug
 	// Sort low, middle, high
  	//          int middle = ( low + high ) # overflow
	//			=> low/2 + high/2           # worng persision problem
	//			=> low + (high-low)/2		# non overflow 


	// find maxium number don't use if else
	return 0;
}
