#include <stdio.h>
#include <string.h>

FILE *data2read;
char str1[50];
char str2[50];
char str3[50];
int pos1x;int pos1y;int pos2x; int pos2y;

int main()
{
	data2read = fopen("data6.txt","r");

	if (data2read)
	{
		while (fscanf(data2read,"%s %s %d,%d %s %d,%d",str1, str2, &pos1x, &pos1y, str3,  &pos2x, &pos2y) != EOF)
		{
		printf("%s",str1);
		}
	}
	return 0;
}


