#include <stdio.h>
#include <string.h>

int min_distance = 9999;
struct Travel{
	char ville1[15];
	char ville2[15];
	int dist;
};
char Chemins[20][20];
struct Travel Travels[50];
int nb_villes;
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
   if (l == r)
   {
	   strcpy(Chemins[i],a);
	   printf("%s\n", a); 
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


int nbUniqueStrElements(char *tab[],char *endstring)
{
	int i,j;
	int i = 0;
	int j = 0;
	char *TabFoundStrings[100]; 
	while (strcmp(tab[i],*endstringfor))
	{
		strcpy(tab[i++],TabFoundStrings[j]
	}

}

int main(int argc,char *argv[])
{

	initTravels(Travels);
	
	FILE* data2read;
	data2read = fopen("data9.txt","r");
	char dataline [100];
	int i = 0;


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
	
	for (i = 0;i<nb_lignes-1;i++)
	{
		printf("ville 1 : %s \t ville 2 : %s\t distance : %d\n",Travels[i].ville1,Travels[i].ville2,Travels[i].dist);
	}

	// générer tous les parcours possibles et calculer leur distance
	// 1. récupérer le nombre de villes
	i = 1;
	while (strcmp(Travels[i].ville1,"init"))
	{
		if (strcmp(Travels[i].ville1,Travels[i+1].ville1))
		{
			nb_villes+=1;
		}
		i++;
	}




	printf("nombre de villes differentes = %d\n",nb_villes);

	
	

//	printf("shortest route = %d",min_distance);
	return 0;


}

