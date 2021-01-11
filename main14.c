/*--- Day 14: Reindeer Olympics ---

This year is the Reindeer Olympics! Reindeer can fly at high speeds, but 
must rest occasionally to recover their energy. Santa would like to know 
which of his reindeer is fastest, and so he has them race.

Reindeer can only either be flying (always at their top speed) or resting 
(not moving at all), and always spend whole seconds in either state.

For example, suppose you have the following Reindeer:

    Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.
    Dancer can fly 16 km/s for 11 seconds, but then must rest for 162 seconds.

After one second, Comet has gone 14 km, while Dancer has gone 16 km.After 
ten seconds, Comet has gone 140 km, while Dancer has gone 160 km. On the 
eleventh second, Comet begins resting (staying at 140 km), and Dancer 
continues on for a total distance of 176 km. On the 12th second, both
reindeer are resting. They continue to rest until the 138th second, when
Comet flies for another ten seconds. On the 174th second, Dancer flies for
another 11 seconds.

In this example, after the 1000th second, both reindeer are resting, and 
Comet is in the lead at 1120 km (poor Dancer has only gotten 1056 km by
that point). So, in this situation, Comet would win (if the race ended at 
1000 seconds).

Given the descriptions of each reindeer (in your puzzle input), after
exactly 2503 seconds, what distance has the winning reindeer traveled?

--- Part Two ---

Seeing how reindeer move in bursts, Santa decides he's not pleased with the 
old scoring system.

Instead, at the end of each second, he awards one point to the reindeer 
currently in the lead. (If there are multiple reindeer tied for the lead,
they each get one point.) He keeps the traditional 2503 second time limit,
of course, as doing otherwise would be entirely ridiculous.

Given the example reindeer from above, after the first second, Dancer is in 
the lead and gets one point. He stays in the lead until several seconds 
into Comet's second burst: after the 140th second, Comet pulls into the 
lead and gets his first point. Of course, since Dancer had been in the lead 
for the 139 seconds before that, he has accumulated 139 points by the 140th second.

After the 1000th second, Dancer has accumulated 689 points, while poor 
Comet, our old champion, only has 312. So, with the new scoring system, 
Dancer would win (if the race ended at 1000 seconds).

Again given the descriptions of each reindeer (in your puzzle input), after 
exactly 2503 seconds, how many points does the winning reindeer have?

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define XMAX 	200
#define RMAX 	20  
#define LMAX 	20 // valable pour le nom et le nombre de cheveaux
#define PART1 	1
#define PART2 	2

struct reindeer{
	char name[RMAX];
	int speed;
	int stamina;
	int fullrest;
	int energy;
	int rest;
	int race;
	int point;
} herd[20];


// fonction qui compte la course
int running(struct reindeer tab[],int tabLength,int timer)
{
	int i = 0;
	int j = 0;
	int distance;
	
	for (i = 0;i<timer;i++)
	{
		for (j = 0 ; j<tabLength ; j++)
		{
			if (tab[j].energy>0)
			{			
				tab[j].race+=tab[j].speed;
				tab[j].energy--;
			}
			else
			{
				tab[j].rest++;
				if (tab[j].rest == tab[j].fullrest) 
				{
					tab[j].energy = tab[j].stamina;
					tab[j].rest = 0;
				}
			}
			
		}
	}
	
	for (i = 0 ; i < tabLength ; i++)
	{
		
		
		if (tab[i].race > distance) 
		{
			distance = tab[i].race;
		}
	}
	
	for (i=0;i<tabLength;i++)
	{
		printf("\n%s\t%d\n",tab[i].name,tab[i].race);
	}
	
	return distance;
	
}

// fonction qui compte la course a points
int runningPoint(struct reindeer tab[],int tabLength,int timer)
{
	int i = 0;
	int j = 0;
	int raceLeader = 0;
	int rankAwarded = 0;
	int pointsMax = 0;
	
	for (i = 0;i<timer;i++)
	{
		for (j = 0 ; j<tabLength ; j++)
		{
			if (tab[j].energy>0)
			{			
				tab[j].race+=tab[j].speed;
				tab[j].energy--;
			}
			else
			{
				tab[j].rest++;
				if (tab[j].rest == tab[j].fullrest) 
				{
					tab[j].energy = tab[j].stamina;
					tab[j].rest = 0;
				}
			}	
		}
		
		for (j= 0 ; j<tabLength ; j++)
		{
			if (tab[j].race > raceLeader) 
			{ 
				rankAwarded = j;
				raceLeader = tab[j].race;
			}
		}
		
		tab[rankAwarded].point +=1;
	}
	
	for (i = 0 ; i < tabLength ; i++)
	{
		if (tab[i].point > pointsMax) 
		{
			pointsMax = tab[i].point;
		}
	}
		
	return pointsMax;
}



int main(int argc, char *argv[])
{

	char dataline[XMAX];
	FILE* datafile = fopen("data14.txt","r");
	int i = 0;
	int val = 0;
	int totalRunTime = 0;
	char *ptr;
	int part = 0;
	int nbReindeer = 0;
	
	if (argv[1] == NULL) || !strcmp(argv[1],"part1"))
	{
		part = PART1;
	}
	else if (!strcmp(argv[1],"part2"))
	{
		part = PART2;
	}
	else
	{
		part = PART1;
	}
	if (argc == 3) 
	{
		totalRunTime = strtol(argv[2],&ptr,10);
	}
		
	// init herd
	for (i = 0; i<LMAX;i++)
	{
		strcpy(herd[i].name,"\0");
		herd[i].speed = 0;
		herd[i].stamina = 0;
		herd[i].fullrest = 0;
		herd[i].energy = 0;
		herd[i].rest = 0;
		herd[i].race = 0;
		herd[i].point = 0;
	}
	
	//open file
	if (datafile == NULL)
	{
		printf("error opening file\n");
		return 0;
	}
	
	i = 0;
	
	while(fgets(dataline,XMAX,datafile) != NULL)
	{
		char *storeline = dataline;

		while (*storeline)
		{
			//printf("%c\n",*storeline);
			if (isdigit(*storeline))
			{
				val = strtol(storeline,&storeline,10);
				
				
				if (herd[i].speed == 0) 
				{
					herd[i].speed = val;
				}
				else if (herd[i].stamina == 0)
				{
					herd[i].stamina = val;
					herd[i].energy = val;
				}
				else
				{
					herd[i].fullrest = val;
				}
			}
			
			else
			{
				storeline++;
			}
		}
		
		strcpy(herd[i++].name,strtok(dataline," "));
	}
	
	nbReindeer = i;
	for (i = 0; i<nbReindeer; i++)
	{
		printf("%s\t%d\t%d\t%d\t%d\n",herd[i].name,herd[i].speed,herd[i].stamina,herd[i].fullrest,herd[i].race);
	}
	
	switch(part)
	{
		case PART1 :
			printf("partie 1 pendant %d secondes\n",totalRunTime);
			printf("distance max run : %d\n",running(herd,nbReindeer,totalRunTime));
			break;
		case PART2 :
			printf("partie 2 pendant %d secondes\n",totalRunTime);
			printf("Le vainqueur aux point a %d points\n",runningPoint(herd,nbReindeer,totalRunTime));
			break;
	}	
	
	return 0;
}
