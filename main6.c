/* 
 
--- Day 6: Probably a Fire Hazard ---

Because your neighbors keep defeating you in the holiday house decorating contest 
year after year, you've decided to deploy one million lights in a 1000x1000 grid.

Furthermore, because you've been especially nice this year, Santa has mailed you 
instructions on how to display the ideal lighting configuration.

Lights in your grid are numbered from 0 to 999 in each direction; the lights at 
each corner are at 0,0, 0,999, 999,999, and 999,0. The instructions include whether 
to turn on, turn off, or toggle various inclusive ranges given as coordinate pairs. 
Each coordinate pair represents opposite corners of a rectangle, inclusive; 
a coordinate pair like 0,0 through 2,2 therefore refers to 9 lights in a 3x3 square. 
The lights all start turned off.

To defeat your neighbors this year, all you have to do is set up your lights by 
doing the instructions Santa sent you in order.

For example:

    turn on 0,0 through 999,999 would turn on (or leave on) every light.
    toggle 0,0 through 999,0 would toggle the first line of 1000 lights, 
    turning off the ones that were on, and turning on the ones that were off.
    turn off 499,499 through 500,500 would turn off (or leave off) the middle four lights.

After following the instructions, how many lights are lit?


--- Part Two ---

You just finish implementing your winning light pattern when you realize you 
mistranslated Santa's message from Ancient Nordic Elvish.
The light grid you bought actually has individual brightness controls; each light
can have a brightness of zero or more. The lights all start at zero.
The phrase turn on actually means that you should increase the brightness of those lights by 1.
The phrase turn off actually means that you should decrease the brightness of those lights by 1, 
to a minimum of zero.
The phrase toggle actually means that you should increase the brightness of those lights by 2.
What is the total brightness of all lights combined after following Santa's instructions?

For example:

    turn on 0,0 through 0,0 would increase the total brightness by 1.
    toggle 0,0 through 999,999 would increase the total brightness by 2000000.

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define PART1 1
#define PART2 2



FILE *data2read;
char dataline[50];
int lightRoom[1000][1000];
int compteur = 0;
int nbOn = 0;
int nbOff = 0;
int nbToggle = 0;


int part = PART2;



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
			switch(part){
				case PART1:
					if (lightRoom[i][j] == 0)
					{
						lightRoom[i][j] = 1;
					}
					else
					{
						lightRoom[i][j] = 0;
					}
				break;
	
				case PART2:
					lightRoom[i][j] +=2;
				break;
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
			switch (part){
				case PART1:
					lightRoom[i][j] = 1;
				break;

				case PART2:
					lightRoom[i][j] += 1;
				break;

			}

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
			switch (part){
				case PART1:
					lightRoom[i][j] = 0;
				break;

				case PART2:
					lightRoom[i][j] -=1;
					if (lightRoom[i][j] < 0) lightRoom[i][j] = 0;
				break;
			}
		}
	}
}



int main(int argc, char * argv[])
{
	printf("%s\n",argv[1]);

	if (!strcmp(argv[1],"part2"))
	{
		part = PART2;
		printf("DAY 6 : PART 2\n");
	}
	else
	{
		part = PART1;
		printf("DAY 6 : PART 1\n");
	}


	data2read = fopen("data6.txt","r");

	if (data2read)
	{
		while ((fgets(dataline,sizeof(dataline)/sizeof(char),data2read ))!=NULL)
		{
			//printf("%s\n",dataline);
			int i = 0;
			int coord[4];
			char *p = dataline;
			while(*p)
			{
				if (isdigit(*p))
				{
					coord[i] = strtol(p,&p,10);
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
				//printf("%d\t%d\t%d\t%d\n",coord[0],coord[1],coord[2],coord[3]);
				turnOn(coord[0],coord[1],coord[2],coord[3]);
			}

			if(strstr(dataline,"off")!=NULL)
			{
				nbOff++;
				//printf("%d\t%d\t%d\t%d\n",coord[0],coord[1],coord[2],coord[3]);
				turnOff(coord[0],coord[1],coord[2],coord[3]);
			}

			if(strstr(dataline,"toggle")!=NULL)
			{	
				nbToggle++;
				//printf("%d\t%d\t%d\t%d\n",coord[0],coord[1],coord[2],coord[3]);
				toggle(coord[0],coord[1],coord[2],coord[3]);
			}



		
		}

		int i;
		int j;

		for (i=0; i<1000; i++)
		{
			for (j=0; j<1000; j++)
			{	
				switch(part){
					case PART1 :
						if (lightRoom[i][j] == 1) compteur++;
					break;

					case PART2:
						compteur += lightRoom[i][j];
					break;
				}
			}
		}
	}

	printf("nb on : %d\n",nbOn);
	printf("nb off : %d\n",nbOff);
	printf("nb Toggle : %d\n",nbToggle);

	printf("nombre de lumières allumées : %d\n",compteur);
	return 0;
}


