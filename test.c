/* 	--- Day 12: JSAbacusFramework.io ---  

Santa's Accounting-Elves need help balancing the books after a recent order. 
Unfortunately, their accounting software uses a peculiar storage format. 
That's where you come in.  They have a JSON document which contains a variety of things: arrays ([1,2,3]),
objects ({"a":1, "b":2}), numbers, and strings. Your first job is to simply find all of the numbers 
throughout the document and add them together.  
For example:    [1,2,3] and {"a":2,"b":4} both have a sum of 6.
		[[[3]]] and {"a":{"b":4},"c":-1} both have a sum of 3.
		{"a":[-1,1]} and [-1,{"a":1}] both have a sum of 0.
	   	[] and {} both have a sum of 0.  
		
You will not encounter any strings containing numbers.  What is the sum of all numbers in the document?i


--- Part Two ---

Uh oh - the Accounting-Elves have realized that they double-counted everything red.

Ignore any object (and all of its children) which has any property with the value "red". 
Do this only for objects ({...}), not arrays ([...]).

    [1,2,3] still has a sum of 6.
    [1,{"c":"red","b":2},3] now has a sum of 4, because the middle object is ignored.
    {"d":"red","e":[1,2,3,4],"f":5} now has a sum of 0, because the entire structure is ignored.
    [1,"red",5] has a sum of 6, because "red" in an array has no effect.



*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/mnt/f/Programmation/advent2015/cJSON.h"

cJSON *pnode[20];



void affiche(cJSON *element,int compteur,int tabulation)
{
	int dep;
	char *tabType;
	//if (compteur <60)
	{
	printf("%d ",compteur);
	if (element->type == 0) tabType = "Invalid";
	if (element->type == 1) tabType = "False";
	if (element->type == 2) tabType = "True";
	if (element->type == 4) tabType = "NULL";
	if (element->type == 8) tabType = "Number";
	if (element->type == 16) tabType = "String";
	if (element->type == 32) tabType = "Array";
	if (element->type == 64) tabType = "Object";


	for (dep = 0;dep <tabulation;dep++) printf("\t");
	printf("%6s\t%s\t%s\t%p\n", element->string, element->valuestring,tabType, element);
	}

}



void iterate(cJSON *element)
{
	static int compteur = 0;
	static int i = 0;
	static int tab = 0;
	cJSON *temp = NULL;
	//if (i>0) printf("i = %d et le noeud correspondant est %s\n",i,pnode[i-1]->string);
	//else printf("\n");
	compteur++;

	//if (compteur >2) printf("type= %d\tvalue = %s\t",element->type,element->valuestring);
	//if (compteur > 2 && !strcmp(element->valuestring,"red") && cJSON_IsObject(pnode[i]))
	
	if (cJSON_IsString(element))
	{	
	if (compteur >2 && compteur<500)
	{
		if (compteur > 2 && pnode[i-1]->type == 64 && !strcmp(element->valuestring,"red"))
		{
			printf("elimination détectée !!!!\n");
			while (temp == NULL)
			{
				temp = pnode[i-1]->next;
				i--;
				tab--;
			}
			//cJSON_DetachItemViaPointer(pnode[i-2],pnode[i-1]);
				cJSON_Delete(pnode[i-2]);
			printf("saut vers : %d\n",temp->type);
			iterate(temp);
		}
	}
	}


	temp = element->child;
	if (temp !=NULL)
	{
		tab++;
		pnode[i++] = element;
		affiche(temp,compteur,tab);
		iterate(temp);
	}
	else 
	{
		temp = element->next;
		if(temp !=NULL)
		{
			affiche(temp,compteur,tab);
			iterate(temp);
		}
		else
		{
			while (temp == NULL)
			{
				tab--;
				temp = pnode[i-1]->next;
				i--;
				//printf("i = %d\n",i);
				if (i == 0) 
				{
					printf("\nfin de json\n");
					//return 0;
				}
			}
			affiche(temp,compteur,tab);
			iterate(temp);
		}

	}
}




int main(int argc,char *argv[])
{
	FILE* data2read;
	//int compteur = 0;
	
	data2read = fopen("data12bis.txt","r");

	if(data2read == NULL) 
	{
		perror("Error in opening file");
	 	return(-1);	
	}

	//char c;
	//char *ptr;
	//char str[10];
	//int i = 0;

	// part1

/*	while ((c = fgetc(data2read)) != EOF)
	{
		//printf("c = %c\n",c);
		if (c == '-' || (c >= '0' && c <= '9'))
		{
			str[i++] = c;		
		}
		else
		{
			str[i]='\0';
			i = 0;
			//printf("str = %s\n",str);
			compteur += strtol(str,&ptr,10);
			str[0] = '\0';

		}
	}
	printf("compteur = %d\n",compteur);

	return 0;

*/

	// part2
	
	char buffer[50000];
	cJSON *jBuffer;

	printf("debut du programme\n");
	
	fgets(buffer, 50000,data2read);
	jBuffer = cJSON_Parse(buffer);
	iterate(jBuffer);
}

