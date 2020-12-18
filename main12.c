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
		
You will not encounter any strings containing numbers.  What is the sum of all numbers in the document?


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
//int i=0;

#define PART1 1
#define PART2 2

int ligne = 0;
cJSON *tab[10];
int tabRed[10] = {0};
int tabCompteur[10];
int maxdepth = 0;
int i = 0;
int end = 0;
int compteurBuffer =0;
int part = 0;
char c;
char *ptr;
char str[10];
char buffer[50000];
FILE* data2read;
cJSON *jBuffer;
cJSON *element;

void show(cJSON *array[],int j)
{
	char JSONType[20];
	int n = 0;
	if (cJSON_IsArray(array[j])) 
		{
			strcpy(JSONType,"array");
		}
		else if (cJSON_IsObject(array[j])) 
		{
			strcpy(JSONType,"object");
		}
		else
		{
			strcpy(JSONType,"item");
		}
		
		printf("%d\t",ligne);
		printf("%d\t",j);
		for ( n = 0 ; n <= j; n++) printf ("  ");
		printf("%s is an %s with value ",array[j]->string, JSONType);
		if (cJSON_IsString(array[j]) == 1)
		{
			printf("%s",cJSON_GetStringValue(array[j]));
		}
		else
		{
			printf("%4.0f",cJSON_GetNumberValue(array[j]));
		}
		printf("\n");
}


void iterate(cJSON *element,cJSON *buffer)
{
	while (!end)
	{		
		ligne ++;
		tab[i] = element;
		
		show(tab,i);
	
		if (cJSON_IsNumber(tab[i])) tabCompteur[i]+=cJSON_GetNumberValue(tab[i]);
		if (cJSON_IsObject(tab[i-1]) && (cJSON_IsString(tab[i])) && (!strcmp(cJSON_GetStringValue(tab[i]),"red"))) tabRed[i-1] = 1; 
		
		element = element->child;

		if (element !=NULL)
		{
			i++;
			iterate(element,buffer);
		}
		else 
		{
			element = tab[i]->next;

			if(element !=NULL)
			{
				iterate(element,buffer);
			}
			else
			{
				do 
				{
					if (i>0) i--;
					element = tab[i];
					if (i==0) printf("i =%d\n",i);
					if(tabRed[i]==0) 
					{
						tabCompteur[i]+=tabCompteur[i+1];
						tabCompteur[i+1]=0;
					}
					else
					{
						tabRed[i] = 0;
						tabCompteur[i+1]=0;
					}
					
					
				}
				while (element->next == NULL && i>0);
				
				if (i==0)
				{
					printf ("\nfin de la liste\n");
					end = 1;
				}
				
				iterate(element->next,buffer);
			}
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
	
	data2read = fopen("data12.txt","r");
	if(data2read == NULL) 
	{
		perror("Error in opening file");
	 	return(-1);	
	}
	
	switch(part)
	{
		case PART1:
		// part1
			
			while ((c = fgetc(data2read)) != EOF)
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
					ligne += strtol(str,&ptr,10);
					str[0] = '\0';

				}
			}
			printf("ligne = %d\n",ligne);

			return 0;

	
		break;
		
		case PART2:
		// part2

			printf("debut du programme...\n");
			
			fgets(buffer, 50000,data2read);
			jBuffer = cJSON_Parse(buffer);
			element=jBuffer;
			iterate(element,jBuffer);
			

			printf("compteur = %d\n",tabCompteur[0]);
			
		break;
	}
}

