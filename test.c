

#include <stdio.h>
#include <stdlib.h>
#define NB 3

void permut(int tab[],int n,int m);
void generate(int k,int *tab);



void generate(int k,int *tab)
{
	
	if (k == 1)
	{
		for (int z=0;z<NB;z++)
		{
			printf("%d\n",tab[z]);
		}
		printf("\n");
	}
	else
	{
		generate(k-1,tab);
		
		for (int i=0;i<k-1;i++)
		{
			if (k%2 == 0)
			{
				permut(tab,i,k-1);
			}
			else
			{
				permut(tab,0,k-1);
			}
		
			generate(k-1,tab);
		}
	}
}

void permut(int tab[],int n,int m)
{
	int stock;
	stock = tab[n];
	tab[n] = tab[m];
	tab[m] = stock;
}


int main () {
   int str[NB] = {1,2,3};
   
   generate(NB,str);

   return(0);
}