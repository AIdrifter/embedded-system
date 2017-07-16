#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdint.h>
#include <unistd.h>
#include <semaphore.h>

// http://blog.csdn.net/chdhust/article/details/10579001

int main() {
	for (int i = 0; i < 3; i++) {
		printf("before fork   me %u  parent %u loop %d\n",getpid(),getppid(),i);
		fork();
		printf("after fork(-) me %u  parent %u  loop %d\n",getpid(),getppid(),i);
	}
	wait(NULL); wait(NULL); wait(NULL);
	sleep(20);
	return 0;
}
