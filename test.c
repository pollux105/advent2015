#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// compte le nombre de chaines uniques dans un tableau

char *data[] = {"test1","test2","test3","test7","test4","test4","test7","test6","test6","test7","init"};
char *end = "init";

int nbStringElements(char *tab[],char *endString)
{
	int i = 0;
	int j = 0;
	int doublon = 0;
	int nbElements = 0;

	char *TabStringFound[50];
	while(strcmp(tab[i],endString))
	{
		j = 0;
		printf("i = %d\tnbElements = %d\n",i,nbElements);
		while (j<nbElements)
		{
			printf("TabStringFound[%d] = %s\tTab[%d] = %s\n",j,TabStringFound[j],i,tab[i]);
			if(!strcmp(TabStringFound[j],tab[i]))
			{
				doublon = 1;
				printf("doublon trouvé !!!\n");
			}
			j++;
		}

		if (doublon) 	// on va chercher plus loin dans le tableau de données d'entrée
		{
			i++;
			doublon = 0;
		}
		else		// on rajoute un élément puis on va chercher plus loin
		{
			printf("---------ecriture------\n");
			TabStringFound[nbElements] = malloc(strlen(tab[i]+1));
			strcpy(TabStringFound[nbElements++],tab[i++]);
		}
	}

	return nbElements;
}

int main()
{
	printf("nombre d'elements different = %d\n",nbStringElements(data,end));
	return 0;
}

