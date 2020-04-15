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

int initTravels(struct Travel *Tableau)
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
	int nb_chemins = 0;
	char shortest_chemin[50];
	int static distance_min = 0;
	int distance = 0;
	int comp1 = 0;			//comp1 = 1 si les deux villes comparées sont équivalentes;
	int comp2 = 0;			//comp2 = 1 si les deux villes comparées sont équivalentes;
	int comp3 = 0;
	int comp4 = 0;
	if (l == r)
	{
		printf("%s\n", a);
		
		//calcul distance
		x = 0; y = 0;
		distance = 0;
		while(x<strlen(a)-1)
		{
			//printf("LIGNE _________ ville[x+1] = %s\n",VillesUniques[a[x+1]-'0']);
			//printf("LIGNE _________ ville[x+1] = %s\n",VillesUniques[a[x+1]-'0']);
			//printf("Vil[%d] = %s  \tVil[%d] = %s  \t",x,VillesUniques[a[x]-'0'],x+1,VillesUniques[a[x+1]-'0']);
			//printf("Ville[%d] = %s\n",x+1,VillesUniques[a[x+1]-'0']);
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
					//printf("y = %d\n",y++);
					y++;
				}
			}
		
			//printf("distance = %d\n",distance);
   			x++;
		}
		distance_min = (distance > distance_min) ? distance : distance_min;
		printf("distance max = %d\n",distance_min);

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
	

	//	printf("shortest route = %d",min_distance);
/*	
	for (i=0;i<=nb_lignes;i++)
	{
		free(Villes[i]);
	}
*/
	return 0;


}

