#include <stdio.h>
#include <string.h>


FILE *data2read;
char dataline[50];
char firstChar[1];
struct wire
{
	char identifier[3];
	int signal;
};

struct wire Ensemble[300];

void printString(char *ch)
{
	int i = 0;
	while (ch[i] !=10) 
	{
		putchar(ch[i]);
		i++;
	}

}


int main(int argc,char * argv[] )
{
	int i;
	
	for (i = 0; i<300;i++)
	{
		strcpy(Ensemble[i].identifier,"\0");
		Ensemble[i].signal = -1;
	}


	data2read = fopen("data7.txt","r");
	
	i = 0;

	while(fgets(dataline,sizeof(dataline)/sizeof(char),data2read)!= NULL)
	{
		strncpy(firstChar,dataline,1);
		printf("dataline :");
		printString(dataline);
		printf("\tpremier caractère : %c\n",firstChar[0]);
		
		if (isdigit(firstChar[0]))
		{
			printf("CARACTERE DIGITAL TROUVE");
			char temp[20];
			int value;
			sscanf(dataline,"%d%*[ -> ]%s",&value,temp);
			strcpy(Ensemble[i].identifier,temp);
			printf("\nCHAINE \t%s\n",temp);
			Ensemble[i].signal = value;
			i++;
			
		
		}
	}

		
		
	int j = 0;
	while (Ensemble[j].signal != -1)
	{
		printf("%s\t%d\n",Ensemble[j].identifier,Ensemble[j].signal);
		j++;
	}
	
	return 0;
}


