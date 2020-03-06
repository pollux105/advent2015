/*  --- Day 3: Perfectly Spherical Houses in a Vacuum ---


Santa is delivering presents to an infinite two-dimensional grid of houses.

He begins by delivering a present to the house at his starting location, 
and then an elf at the North Pole calls him via radio and tells him where to move next.
Moves are always exactly one house to the north (^), south (v), east (>), or west (<).
After each move, he delivers another present to the house at his new location.

However, the elf back at the north pole has had a little too much eggnog, 
and so his directions are a little off, and Santa ends up visiting some houses more than once. 

How many houses receive at least one present?

For example:

    > delivers presents to 2 houses: one at the starting location, and one to the east.
    ^>v< delivers presents to 4 houses in a square, including twice to the house at his starting/ending location.
    ^v^v^v^v^v delivers a bunch of presents to some very lucky children at only 2 houses.


	Correspondances ASCII :
	^ = 94
	< = 60
	> = 62
	v = 118

*/ 


#include <stdio.h>

#define XMAX 300
#define YMAX 300


int main()
{

	FILE *data2read;
	int Map[XMAX][YMAX];
	

	int posx = XMAX/2;
	int posy = YMAX/2;
	int posxrobo = XMAX/2;
	int posyrobo = YMAX/2;
	int i,j;
	int tour = 0;
	int HappyHouses = 0;
	char c;

	printf("début du programme\n");

	for (i = 0;i < XMAX; i++)
	{
		for (j = 0; j < YMAX; j++)
		{
			Map[i][j] = 0;
		}
	}


	data2read = fopen("data.txt","r");

	if(data2read)
	{
		while ((c = getc(data2read)) != EOF )
		{
			if (tour == 0)
			{	
				if (c == 94) posy-=1;
				else if (c == 118) posy +=1;
				else if (c == 60) posx -=1;
				else if (c == 62) posx +=1;
				else 
				{
					printf("caractère non reconnu\n");
				}
			Map[posx][posy] = 1;
			tour = 1;
			}
			
			else if (tour == 1)
			{
				if (c == 94) posyrobo-=1;
				else if (c == 118) posyrobo +=1;
				else if (c == 60) posxrobo -=1;
				else if (c == 62) posxrobo +=1;
				else 
				{
					printf("caractère non reconnu\n");
				}
			Map[posxrobo][posyrobo] = 1;
			tour = 0;
			}

			printf("caractere = %c\tposx = %d\tposy = %d\n",c,posx,posy);
					}
			
	}
	else 
	{
		printf("fichier introuvable");
	}

	for (i = 0; i < XMAX; i++)
	{
		for (j = 0; j < YMAX; j++)
		{
			if (Map[i][j] > 0) HappyHouses +=1;
		}
	}

	printf("le nombre de maisons servies est de : %d\n",HappyHouses);
	return 0;
}
