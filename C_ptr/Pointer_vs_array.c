#include <stdio.h>

int main(){
	// 在declaration 時 
	// pointer != array , but 在expression時兩者是等價的
    int x[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("%d %d %d %d\n", x[4], *(x + 4), *(4 + x), 4[x]);
    //printf("%d %d %d %d\n", x[4], *(x - 4), *(4 - x), 4[x]);  type conversions
}
