/*--- Day 13: Knights of the Dinner Table ---

In years past, the holiday feast with your family hasn't gone so well. Not everyone gets along! This year, you resolve, will be different. You're going to find the optimal seating arrangement and avoid all those awkward conversations.

You start by writing up a list of everyone invited and the amount their happiness would increase or decrease if they were to find themselves sitting next to each other person. You have a circular table that will be just big enough to fit everyone comfortably, and so each person will have exactly two neighbors.

For example, suppose you have only four attendees planned, and you calculate their potential happiness as follows:

Alice would gain 54 happiness units by sitting next to Bob.
Alice would lose 79 happiness units by sitting next to Carol.
Alice would lose 2 happiness units by sitting next to David.
Bob would gain 83 happiness units by sitting next to Alice.
Bob would lose 7 happiness units by sitting next to Carol.
Bob would lose 63 happiness units by sitting next to David.
Carol would lose 62 happiness units by sitting next to Alice.
Carol would gain 60 happiness units by sitting next to Bob.
Carol would gain 55 happiness units by sitting next to David.
David would gain 46 happiness units by sitting next to Alice.
David would lose 7 happiness units by sitting next to Bob.
David would gain 41 happiness units by sitting next to Carol.

Then, if you seat Alice next to David, Alice would lose 2 happiness units (because David talks so much), but David would gain 46 happiness units (because Alice is such a good listener), for a total change of 44.

If you continue around the table, you could then seat Bob next to Alice (Bob gains 83, Alice gains 54). Finally, seat Carol, who sits next to Bob (Carol gains 60, Bob loses 7) and David (Carol gains 55, David gains 41). The arrangement looks like this:

     +41 +46
+55   David    -2
Carol       Alice
+60    Bob    +54
     -7  +83

After trying every other seating arrangement in this hypothetical scenario, you find that this one is the most optimal, with a total change in happiness of 330.

What is the total change in happiness for the optimal seating arrangement of the actual guest list?

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PART1 1
#define PART2 2
#define XMAX 200

FILE* data2read;
int k;
char names[20][30];
char dataline[XMAX];
int part;
int stored = 0;
int namesIncrementer = 0;
int lovePowerMax = 0;

struct love{
	char names1[20];
	char names2[20];
	int lovepower;
} lovetab[XMAX];

	


/* 
void gHEAP(int k,char tab[20][30]);
void permut(struct love *tab,int n, int m);
 */

void permut(char tab[20][30],int n,int m)
{
	char c[30] = "toto";
	strcpy(c,tab[n]);
	strcpy(tab[n],tab[m]);
	strcpy(tab[m],c);
}


void gHEAP(int k,char tab[20][30])
{
	static int nbArrangement = 0;
	
	int lovePowerTemp = 0;
	int y = 0;
	int count = 0;
	if (k == 1) 
	{
		printf("%d\t",nbArrangement);
		for (int i = 0;i<namesIncrementer;i++)
		{
			printf("%s\t",tab[i]);
		}
		printf("\t");
		nbArrangement++;
		
		
		// cherche le love power de j entre 0 et le nombre d'invites
		for (int j=0;j<namesIncrementer-1;j++)
		{
			while(1)
			{
				if ( (!strcmp(lovetab[y].names1,tab[j]) && !strcmp(lovetab[y].names2,tab[j+1]))
					|| (!strcmp(lovetab[y].names2,tab[j]) && !strcmp(lovetab[y].names1,tab[j+1])))
				{
					printf("neighbour found : %s\t\%s\t",lovetab[y].names1,lovetab[y].names2);
					lovePowerTemp += lovetab[y].lovepower;
					printf("love count = %d\t love add = %d\n",lovetab[y].lovepower,lovePowerTemp);
					
					y=0;
					count += 1;
					if (count == 2)
					{
						count = 0;
						break;
					}
				}
				else
				{
					
					//printf("... y = %d\n",y);
					y++;
				}
			}
			
		}
		
		// cherche le love power entre le premier et le dernier invite
		while(1)
		{
			if ( (!strcmp(lovetab[y].names1,tab[0]) && !strcmp(lovetab[y].names2,tab[namesIncrementer-1]))
				|| (!strcmp(lovetab[y].names2,tab[0]) && !strcmp(lovetab[y].names1,tab[namesIncrementer-1])))
			{
				//printf("rotate found : %s\t\%s\n",lovetab[y].names1,lovetab[y].names2);
				lovePowerTemp += lovetab[y].lovepower;
				y=0;
				if (count == 2)
				{
					count = 0;
					break;
				}
				break;
			}
			else
			{
				
				//printf("... y = %d\n",y);
				y++;
			}
		}
		if (lovePowerTemp>lovePowerMax) lovePowerMax = lovePowerTemp;
		printf("\ttemp = %d \t lovemax = %d\n",lovePowerTemp,lovePowerMax);
		
		
		
	}
	else	
	{
		gHEAP(k-1,tab);
		
		for (int i=0;i<=k-2;i++)
		{
			if (i%2 == 0)
			{
				permut(tab,i,k-1);
			}
			else
			{
				permut(tab,0,k-1);
			}
		
			gHEAP(k-1,tab);
		}
	}
}


int main(int argc,char *argv[])
{
	
	if (argv[1] == NULL)
	{
		part = PART1;
	}
	else if (!strcmp(argv[1],"part1"))
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
	
	data2read = fopen("data13bis.txt","r");
	if(data2read == NULL) 
	{
		perror("Error in opening file");
	 	return(-1);	
	}
	
	int i = 0;
	
	while (fgets(dataline,XMAX,data2read) != NULL)
	{
		
		char datastore[XMAX];
		int k = 0;
		int sign = 1;
		char *ptr;
		
		
		strcpy(datastore,dataline);
		// premier nom
		strcpy(lovetab[i].names1,strtok(dataline," "));
		// dernier nom
		strcpy(lovetab[i].names2,(strrchr(datastore,' ')+1));
		for (int j = 0;j<20;j++)
		{
			if (lovetab[i].names2[j] == '.') 
			{
				lovetab[i].names2[j] = '\0';
			}
		}		
		// gain or lose
		if (strstr(datastore,"gain") == NULL) sign = -1;
		// amount of love to lose or gain
		for (int j=0;j<=200;j++)
		{
			if (datastore[j] >= '0' && datastore[j] <= '9')
			{
				k = j;
				break;
			}
		}
		lovetab[i].lovepower = strtol(datastore+k,&ptr,10)*sign;
		i++;
	}
	
	
	for (int j=0;j<i;j++)
	{
		printf("%s\t\t%s\t\t%d\n",lovetab[j].names1,lovetab[j].names2,lovetab[j].lovepower);
		for (k=0;k<=j;k++)
		{
			if (strcmp(names[k],lovetab[j].names1) == 0)
			{
				stored = 1;
			}
		}
		if (stored == 0)
		{
			strcpy(names[namesIncrementer++],lovetab[j].names1);
			printf("ajoute\n");
		}
		stored = 0;
	}
	
	k=0;
	
	while (strcmp(names[k],""))
	
	{
		printf("%d\t%s\n",k,names[k]);
		k++;
	}
	printf("\n");
	
	
	
	gHEAP(k+1,names);
	printf("Amour final le plus eleve : %d\n",lovePowerMax);
	return 0;
}