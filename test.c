#include <stdio.h>
#include <limits.h>


int main(void)
{
	unsigned short i = 123;
	unsigned short j = 0;
	
	j = ~i;
	printf("%d\t%d\n",i,~i);


  return 0;
}
