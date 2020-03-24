#include <stdio.h>
#include <string.h>

#define XMAX 100

int BRUT = 0;
int cumulBRUT;
int FINE = 0;
int cumulFINE;
char dataline[XMAX];
int escape = 0;
int i;

void main(int argc, char * argv[])
{

	FILE* data2read;
	data2read = fopen("data8.txt","r");
	
	while (fgets(dataline,XMAX,data2read) != NULL){
	i = 0;
		printf("dataline : %s",dataline);
		while (dataline[i] != '\0')
		{
			printf ("i = %d\tCHAR = %d\n",i,dataline[i]);
			if (dataline[i] == '\\')
			{
				//printf("\nechappement\n");
				//printf("[i+1] = %d\t[i+2] = %d\n",dataline[i+1],dataline[i+2]);
				//printf("0 -> 9 : %d %d || \t A - F : %d %d\t ||a -> f : %d %d\n",'0','9','A','F','a','f');
				if (dataline[i+1] == 'x' && ((dataline[i+2] >= '0' && dataline[i+2] <= '9') \
							|| (dataline[i+2] >= 'A' && dataline[i+2] <= 'F') \
							|| (dataline[i+2] >= 'a' && dataline[i+2] <= 'f')) \
							&& ((dataline[i+3] >= '0' && dataline[i+3] <= '9') \
							|| (dataline[i+3] >= 'A' && dataline[i+3] <= 'F') \
							|| (dataline[i+3] >= 'a' && dataline[i+3] <= 'f')))
				{
					BRUT += 4;
					FINE += 1;
					i += 4;
				//	printf("test");
				}
			
				else if (dataline[i+1] == '"')
				{
					BRUT += 2;
					FINE += 1;
					i += 2;
				}

				else if (dataline[i+1] == '\\')
				{
					BRUT += 2;
					FINE += 1;
					i += 2;
				}

				else
				{
					i++;
				}

			}
			else if (dataline[i] == 32)
			{
				i+= 1;
				BRUT +=1;
			}
			
			else if (dataline[i] == 10 || dataline[i] == 13)
			{
				break;
			}

			else
			{
				BRUT ++;
				FINE ++;
				i++;
			}
		}

		FINE -=2; // removing starting and trailing double quotes
		printf("BRUT = %d\tFINE = %d\n\n",BRUT,FINE);
		cumulBRUT += BRUT; 
		BRUT= 0;
		cumulFINE +=FINE;
		FINE = 0;
	}

	printf("cBRUT = %d\ncFINE = %d\n",cumulBRUT,cumulFINE);
	printf("RESULTAT = %d",cumulBRUT-cumulFINE);
}


