/*--- Day 15: Science for Hungry People ---

Today, you set out on the task of perfecting your milk-dunking 
cookie recipe. All you have to do is find the right balance of ingredients.

Your recipe leaves room for exactly 100 teaspoons of ingredients. You make 
a list of the remaining ingredients you could use to finish the recipe 
(your puzzle input) and their properties per teaspoon:

 -  capacity (how well it helps the cookie absorb milk)
 -  durability (how well it keeps the cookie intact when full of milk)
 -  flavor (how tasty it makes the cookie)
 -  texture (how it improves the feel of the cookie)
 -  calories (how many calories it adds to the cookie)

You can only measure ingredients in whole-teaspoon amounts accurately, and
you have to be accurate so you can reproduce your results in the future. 
The total score of a cookie can be found by adding up each of the 
properties (negative totals become 0) and then multiplying together 
everything except calories.

For instance, suppose you have these two ingredients:

Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8
Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3

Then, choosing to use 44 teaspoons of butterscotch and 56 teaspoons of 
cinnamon (because the amounts of each ingredient must add up to 100) would 
result in a cookie with the following properties:

-   A capacity of 44*-1 + 56*2 = 68
-   A durability of 44*-2 + 56*3 = 80
-   A flavor of 44*6 + 56*-2 = 152
-   A texture of 44*3 + 56*-1 = 76

Multiplying these together (68 * 80 * 152 * 76, ignoring calories for now) 
results in a total score of 62842880, which happens to be the best score 
possible given these ingredients. If any properties had produced a negative 
total, it would have instead become zero, causing the whole score to 
multiply to zero.

Given the ingredients in your kitchen and their properties, what is the 
total score of the highest-scoring cookie you can make?
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LMAX 10
#define RMAX 20
#define XMAX 200
#define PART1 1
#define PART2 2

/*
struct ingredient{
	char name[20];
	int capacity;
	int durability;
	int flavor;
	int texture;
	int calories;
} availableIngredient[LMAX];
*/

int searchReceipe(int tab[20][20], int part)
{
	int i,j,k,l;
	int capacity = 0;
	int durability = 0;
	int flavor = 0;
	int texture = 0;
	int calories = 0;
	int totalFlavor = 0;
	int maxFlavor = 0;
	
	
	
	for (i=100;i>=0;i--){
		for (j=100-i;j>=0;j--){
			for (k=100-i-j;k>=0;k--)
			{
				l = 100-i-j-k;
				
				capacity 	= i * tab[0][0] + j * tab[1][0] + k * tab[2][0] + l * tab[3][0];
				durability 	= i * tab[0][1] + j * tab[1][1] + k * tab[2][1] + l * tab[3][1];
				flavor 		= i * tab[0][2] + j * tab[1][2] + k * tab[2][2] + l * tab[3][2];
				texture 	= i * tab[0][3] + j * tab[1][3] + k * tab[2][3] + l * tab[3][3];
				calories	= i * tab[0][4] + j * tab[1][4] + k * tab[2][4] + l * tab[3][4];
				
				if (capacity <0) capacity = 0;
				if (durability <0) durability = 0;
				if (flavor <0) flavor = 0;
				if (texture <0) texture = 0;
				
				totalFlavor = capacity * durability * flavor * texture;
				
				switch(part){
					case PART1:
						if (totalFlavor > maxFlavor) maxFlavor = totalFlavor;
					break;
				
					case PART2:
						if (totalFlavor > maxFlavor && calories == 500) maxFlavor = totalFlavor;
					break;
				}
			}
		}
	}
	return maxFlavor;
}



int main(int argc,char *argv[])
{

	FILE* data2read;
	int val;
	char dataline[XMAX];
	int i,j;
	int tabIngredients[20][20];
	int sign = 1;
	int part = 1;
	
	if ((argv[1] == NULL) || !strcmp(argv[1],"part1"))
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
		
	data2read = fopen("data15.txt","r");
	
	if (data2read == NULL)
	{
		printf("file not available");
		return 0;
	}
	
	while(fgets(dataline,XMAX,data2read) != NULL)
	{
		j = 0;
		char *storeline = dataline;
		printf("%s\n",storeline);
				
		while(*storeline)
		{
			if (storeline[0] == 45)
			{
				sign = -1;
				storeline++;
			}
			else if (isdigit(*storeline))
			{
				val = strtol(storeline,&storeline,10);
				tabIngredients[i][j++] = val*sign;
				sign = 1;
			}
			else
			{
			storeline++;
			}

		}
		
		
		
		i++;	
	}
	
	//iMax = i;
	//jMax = j; 
	
	printf("total = %d\n",searchReceipe(tabIngredients,part));
	return 0;
}
