#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
   int i;
   for (i = 0; i < 3; i++) {
       if (fork() == 0)
	   {
           printf("Child sees i = %d (%d)\n ,", i, getpid()); exit(1);
       }
	   else
	   {
	   	   printf("Parent sees i = %d (%d)\n", i,getpid());
	   }
    }
}

