#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

FILE *data2read;
char dataline[50];
int lightRoom[1000][1000];
struct Corner {
	int Xpos;
	int Ypos;
};

struct Corner corner1;
struct Corner corner2;
int compteur = 0;
int nbOn = 0;
int nbOff = 0;
int nbToggle = 0;

void toggle(int X1,int Y1, int X2, int Y2)
{
	int Xmin, Ymin;
	int Xmax, Ymax;
	int i,j;
	
	if (X1 < X2)
	{
		Xmin = X1;
		Xmax = X2;
	}
	else
	{
		Xmin = X2;
		Xmax = X1;
	}

	if (Y1 < Y2)
	{
		Ymin = Y1;
		Ymax = Y2;
	}
	else
	{
		Ymin = Y2;
		Ymax = Y1;
	}


	for ( i = Xmin; i<= Xmax; i++)
	{
		for ( j = Ymin; j <= Ymax; j++)
		{
			if (lightRoom[i][j] == 0)
			{
				lightRoom[i][j] = 1;
			}
			else
			{
				lightRoom[i][j] = 0;
			}
		}
	}
}


void turnOn(int X1,int Y1, int X2, int Y2)
{
	int Xmin, Ymin;
	int Xmax, Ymax;
	int i,j;

	if (X1 < X2)
	{
		Xmin = X1;
		Xmax = X2;
	}
	else
	{
		Xmin = X2;
		Xmax = X1;
	}

	if (Y1 < Y2)
	{
		Ymin = Y1;
		Ymax = Y2;
	}
	else
	{
		Ymin = Y2;
		Ymax = Y1;
	}


	for ( i = Xmin; i <= Xmax; i++)
	{
		for ( j = Ymin; j <= Ymax; j++)
		{
			lightRoom[i][j] = 1;
		}
	}
}

void turnOff(int X1,int Y1, int X2, int Y2)
{
	int Xmin, Ymin;
	int Xmax, Ymax;
	int i,j;

	if (X1 < X2)
	{
		Xmin = X1;
		Xmax = X2;
	}
	else
	{
		Xmin = X2;
		Xmax = X1;
	}

	if (Y1 < Y2)
	{
		Ymin = Y1;
		Ymax = Y2;
	}
	else
	{
		Ymin = Y2;
		Ymax = Y1;
	}

	for ( i = Xmin; i<=Xmax; i++)
	{
		for ( j = Ymin; j <= Ymax; j++)
		{
			lightRoom[i][j] = 0;
		}
	}
}



int main()
{
	data2read = fopen("data6.txt","r");

	if (data2read)
	{
		while ((fgets(dataline,sizeof(dataline)/sizeof(char),data2read ))!=NULL)
		{
			printf("%s\n",dataline);
			int i = 0;
			int coord[4];
			char *p = dataline;
			while(*p != 10)
			{
				printf("%d\n",p);
				if (isdigit(*p))
				{
					coord[i] = strtol(p,&p,10);
					printf("%d\t",coord[i]);
					i++;
				}
				else
				{
					p++;
				}

			}

			
			if(strstr(dataline,"on")!=NULL)
			{
				nbOn++;
				printf("%d\t%d\t%d\t%d\n",coord[1],coord[2],coord[3],coord[4]);
				turnOn(coord[1],coord[2],coord[3],coord[4]);
			}

			if(strstr(dataline,"off")!=NULL)
			{
				nbOff++;
				printf("%d\t%d\t%d\t%d\n",coord[1],coord[2],coord[3],coord[4]);
				turnOff(coord[1],coord[2],coord[3],coord[4]);
			}

			if(strstr(dataline,"toggle")!=NULL)
			{	
				nbToggle++;
				printf("%d\t%d\t%d\t%d\n",coord[1],coord[2],coord[3],coord[4]);
				toggle(coord[1],coord[2],coord[3],coord[4]);
			}



		
		}

		int i;
		int j;

		for (i=0; i<1000; i++)
		{
			for (j=0; j<1000; j++)
			{	
				if (lightRoom[i][j] == 1) compteur++;
			}
		}
	}
	printf("nb on : %d\n",nbOn);
	printf("nb off : %d\n",nbOff);
	printf("nb Toggle : %d\n",nbToggle);

	printf("nombre de lumières allumées : %d\n",compteur);
	return 0;
}


