#include <stdio.h>

static int flag=0;
int p(int i, int N)
{
	flag++;
	printf("[%d] i = %d N = %d \n",flag,i,N);
	// ori
    // return (i < N && printf("%d\n", i) && !p(i + 1, N))
    //         || printf("%d\n", i);


	// hack
    // return (i < N && printf("%d\n", i) && !p(i + 1, N))
    // 		|| (i==N) && printf("%d %d \n",i,i)
    //         || printf("%d\n", i);

	// answer : change item "&&"
	// be careful C operator
    return ( printf("%d\n", i) && i < N && !p(i + 1, N))
            || printf("%d\n", i);


}


int main(){
	p(1,5);
}
