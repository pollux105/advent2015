#include <stdio.h>
#include <string.h>

FILE *data2read;
char dataline[50];
int lightRoom[1000][1000];
struct Corner {
	int Xpos;
	int Ypos;
};

struct Corner corner1;
struct Corner corner2;


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
//			printf("%s\n",dataline);

		}
	}
	return 0;
}


