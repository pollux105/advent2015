/* 
 --- Day 9: All in a Single Night ---  
Every year, Santa manages to deliver all of his presents in a single night.  This year, however, he has some new locations to visit;
his elves have provided him the distances between every pair of locations. 
He can start and end at any two (different) locations he wants, but he must visit each location exactly once. 
What is the shortest distance he can travel to achieve this?  
For example, given the following distances:  
 	London to Dublin = 464 
	London to Belfast = 518 
	Dublin to Belfast = 141  
The possible routes are therefore:  
	Dublin -> London -> Belfast = 982 
	London -> Dublin -> Belfast = 605 
	London -> Belfast -> Dublin = 659 
	Dublin -> Belfast -> London = 659
       	Belfast -> Dublin -> London = 605
       	Belfast -> London -> Dublin = 982
The shortest of these is London -> Dublin -> Belfast = 605, 
and so the answer is 605 in this example.  

What is the distance of the shortest route?  
Your puzzle answer was 117. 

--- Part Two ---  The next year, just to show off, Santa decides to take the route with the longest distance instead.  
He can still start and end at any two (different) locations he wants, and he still must visit each location exactly once.  
For example, given the distances above, the longest route would be 982 via (for example) Dublin -> London -> Belfast.  

What is the distance of the longest route?  Your puzzle answer was 909.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int min_distance = 9999;
struct Travel{
	char ville1[15];
	char ville2[15];
	int dist;
};
char Chemins[20][20];
struct Travel Travels[50];
char *Villes[100];
char *VillesUniques[50];
int nb_villes = 1; //la première ville ne peut pas être comparée à elle même.
int nb_lignes;
int distance_min = 10000;
int distance_max = 0;

void initTravels(struct Travel *Tableau)
{
	int i;
	for (i=0; i<50; i++)
	{
		strcpy(Tableau[i].ville1,"init");
		strcpy(Tableau[i].ville2,"init");
		Tableau[i].dist = 0;
	}
}

void swap(char *s1,char *s2)
{
	char temp;
	temp = *s2;
	*s2 = *s1;
	*s1 = temp;
}

void permute(char *a, int l, int r) 
{ 
	int i;
   	int compteur = 0;
	int x;
	int y;
	int distance = 0;
	int comp1 = 0;			//comp1 = 1 si les deux villes comparées sont équivalentes;
	int comp2 = 0;			//comp2 = 1 si les deux villes comparées sont équivalentes;
	int comp3 = 0;
	int comp4 = 0;
	if (l == r)
	{
		//printf("%s\n", a);
		
		//calcul distance
		x = 0; y = 0;
		distance = 0;
		while(x<strlen(a)-1)
		{
			while(1)
			{
				comp1 = !strcmp(Travels[y].ville1,VillesUniques[a[x]-'0']);
				comp2 = !strcmp(Travels[y].ville2,VillesUniques[a[x+1]-'0']);
				comp3 = !strcmp(Travels[y].ville1,VillesUniques[a[x+1]-'0']);
				comp4 = !strcmp(Travels[y].ville2,VillesUniques[a[x]-'0']);

				if ( (comp1 == 1 && comp2 == 1) || (comp3 == 1 && comp4 == 1))
				{
					distance += Travels[y].dist;
					y = 0;
					break;
				}
				else 
				{
					y++;
				}
			}
   			x++;
		}
		
		distance_min = (distance < distance_min) ? distance : distance_min;
		distance_max = (distance > distance_max) ? distance : distance_max;	
	}
	else
   	{ 
		for (i = l; i <= r; i++) 
		{ 
        		swap((a+l), (a+i)); 
		        permute(a, l+1, r); 
        		swap((a+l), (a+i)); //backtrack 
		} 
	}
	
}


int nbUniqueStrElements(char *TabFoundStrings[],char *tab[],const char *endstring)
{
	int i = 0;
	int j = 0;
	int nbElements = 0;
	int doublon = 0;
	
	//char *TabFoundStrings[50]; 
	while (strcmp(tab[i],endstring))
	{
		j=0;
		while(j<nbElements)
		{
		if (!strcmp(TabFoundStrings[j],tab[i])) doublon = 1;
			j++;
		}
		if (doublon)
		{
			i++;
			doublon = 0;
		}
		else
		{
			TabFoundStrings[nbElements] = malloc(strlen(tab[i])+1);
			strcpy(TabFoundStrings[nbElements++],tab[i++]);
		}
			
	}
	TabFoundStrings[nbElements] = malloc(strlen(endstring+1));
	strcpy(TabFoundStrings[nbElements],endstring);
	return nbElements;
}

int main(int argc,char *argv[])
{

	initTravels(Travels);
	
	FILE* data2read;
	data2read = fopen("data9.txt","r");
	char dataline [100];
	int i = 0;
	int j = 0;

	while (fgets(dataline,100,data2read) != NULL)
	{
		char *token = strtok(dataline," ");
		
		strcpy(Travels[nb_lignes].ville1,token);
		while (token!=NULL)
		{

			if (strcmp(token,"to") && strcmp(token,"="))
			{
				if(isdigit(token[0]))
				{
					Travels[nb_lignes].dist = atoi(token);
				}
				else
				{
					strcpy(Travels[nb_lignes].ville2,token);
				}
			}

			token = strtok(NULL," ");
		}
		
		nb_lignes++;
	}
	
	for (i = 0;i<nb_lignes;i++)
	{
	//	printf("ville 1 : %s \t ville 2 : %s\t distance : %d\n",Travels[i].ville1,Travels[i].ville2,Travels[i].dist);
	}

	// générer tous les parcours possibles et calculer leur distance
	// 1. récupérer le nombre de villes et générer une tableau contenant une fois chaque ville

	i = 0;
	j = 0;
	while (strcmp(Travels[i].ville1,"init"))
	{
		Villes[i] = malloc(strlen(Travels[i].ville1));
		strcpy(Villes[j],Travels[i].ville1);
		i++;j++;
	}
	i = 0;
	while (strcmp(Travels[i].ville2,"init"))
	{
		Villes[j] = malloc(strlen(Travels[i].ville2));
		strcpy(Villes[j],Travels[i].ville2);

		i++;j++;
	}
		
	Villes[j] = malloc(50);
	strcpy(Villes[j],"init");

	nb_villes = nbUniqueStrElements(VillesUniques,Villes,"init");
	printf("NB VILLEs = %d\n",nb_villes);
	
	i=0;
	while(strcmp(VillesUniques[i],"init"))
	{
		printf("ville[%d] : %s\n",i,VillesUniques[i]);
		i++;
	}

	// 2. générer tous les trajets possibles sur nb_villes 
	char brassage[50];
	for (i=0;i<nb_villes;i++)
	{
		brassage[i] = '0'+i;
	}
	brassage[i]= '\0';
	permute(brassage,0,strlen(brassage)-1);

	printf("distance min = %d\t",distance_min);
	printf("distance max = %d\n",distance_max);

		
	return 0;
}

