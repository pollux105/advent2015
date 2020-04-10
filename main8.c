/* --- Day 8: Matchsticks ---

Space on the sleigh is limited this year, and so Santa will be bringing his list as a digital copy.
He needs to know how much space it will take up when stored.

It is common in many programming languages to provide a way to escape special characters in strings.
For example, C, JavaScript, Perl, Python, and even PHP handle special characters in very similar ways.

However, it is important to realize the difference between the number of characters in the code 
representation of the string literal and the number of characters in the in-memory string itself.

For example:

    "" is 2 characters of code (the two double quotes), but the string contains zero characters.
    "abc" is 5 characters of code, but 3 characters in the string data.
    "aaa\"aaa" is 10 characters of code, but the string itself contains six "a" characters and a single, 
    escaped quote character, for a total of 7 characters in the string data.
    "\x27" is 6 characters of code, but the string itself contains just one - an apostrophe ('), escaped using hexadecimal notation.

Santa's list is a file that contains many double-quoted string literals, one on each line. 
The only escape sequences used are \\ (which represents a single backslash), \" (which represents a lone double-quote character),
and \x plus two hexadecimal characters (which represents a single character with that ASCII code).

Disregarding the whitespace in the file, what is the number of characters of code for string literals 
minus the number of characters in memory for the values of the strings in total for the entire file?

For example, given the four strings above, the total number of characters of string code (2 + 5 + 10 + 6 = 23) 
minus the total number of characters in memory for string values (0 + 3 + 7 + 1 = 11) is 23 - 11 = 12.

--- Part Two ---

Now, let's go the other way. In addition to finding the number of characters of code, 
you should now encode each code representation as a new string and find the number of characters
of the new encoded representation, including the surrounding double quotes.

For example:

    "" encodes to "\"\"", an increase from 2 characters to 6.
    "abc" encodes to "\"abc\"", an increase from 5 characters to 9.
    "aaa\"aaa" encodes to "\"aaa\\\"aaa\"", an increase from 10 characters to 16.
    "\x27" encodes to "\"\\x27\"", an increase from 6 characters to 11.

Your task is to find the total number of characters to represent the newly encoded strings 
minus the number of characters of code in each original string literal. 
For example, for the strings above, the total encoded length (6 + 9 + 16 + 11 = 42) 
minus the characters in the original code representation (23, just like in the first part of this puzzle) is 42 - 23 = 19.
*/

#include <stdio.h>
#include <string.h>

#define XMAX 100
#define PART1 1
#define PART2 2 
int BRUT = 0;
int cumulBRUT;
int FINE = 0;
int cumulFINE;
char dataline[XMAX];
int escape = 0;
int i;
int part;


int main(int argc, char * argv[])
{

	FILE* data2read;
	data2read = fopen("data8.txt","r");
	if (!strcmp(argv[1],"part1"))
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



	switch (part){

	case PART1:
		printf("PART1\n");
		while (fgets(dataline,XMAX,data2read) != NULL){
		i = 0;
			printf("dataline : %s",dataline);
			while (dataline[i] != '\0')
			{
				printf ("i = %d\tCHAR = %d\n",i,dataline[i]);
				if (dataline[i] == '\\')
				{
					//printf("\nechappement\n");
					//printf("[i+1] = %d\t[i+2] = %d\n",dataline[i+1],dataline[i+2]);
					//printf("0 -> 9 : %d %d || \t A - F : %d %d\t ||a -> f : %d %d\n",'0','9','A','F','a','f');
					if (dataline[i+1] == 'x' && ((dataline[i+2] >= '0' && dataline[i+2] <= '9') \
								|| (dataline[i+2] >= 'A' && dataline[i+2] <= 'F') \
								|| (dataline[i+2] >= 'a' && dataline[i+2] <= 'f')) \
								&& ((dataline[i+3] >= '0' && dataline[i+3] <= '9') \
								|| (dataline[i+3] >= 'A' && dataline[i+3] <= 'F') \
								|| (dataline[i+3] >= 'a' && dataline[i+3] <= 'f')))
					{
						BRUT += 4;
						FINE += 1;
						i += 4;
					//	printf("test");
					}
				
					else if (dataline[i+1] == '"')
					{
						BRUT += 2;
						FINE += 1;
						i += 2;
					}

					else if (dataline[i+1] == '\\')
					{
						BRUT += 2;
						FINE += 1;
						i += 2;
					}

					else
					{
						i++;
					}

				}
				else if (dataline[i] == 32)
				{
					i+= 1;
					BRUT +=1;
				}
				
				else if (dataline[i] == 10 || dataline[i] == 13)
				{
					break;
				}

				else
				{
					BRUT ++;
					FINE ++;
					i++;
				}
			}

			FINE -=2; // removing starting and trailing double quotes
			printf("BRUT = %d\tFINE = %d\n\n",BRUT,FINE);
			cumulBRUT += BRUT; 
			BRUT= 0;
			cumulFINE +=FINE;
			FINE = 0;
		}
	
	printf("cBRUT = %d\ncFINE = %d\n",cumulBRUT,cumulFINE);
	printf("RESULTAT = %d",cumulBRUT-cumulFINE);
	break;

	case PART2:
		printf("PART2\n");
		while (fgets(dataline,XMAX,data2read) != NULL){
		i = 0;
			printf("dataline : %s",dataline);
			while (dataline[i] != '\0')
			{
				printf ("i = %d\tCHAR = %c\tBRUT = %d\tFINE = %d\n,",i,dataline[i],BRUT,FINE);
				if (dataline[i] == '\\' || dataline[i] == '"')
				{
						BRUT += 1;
						FINE += 2;
						i += 1;
				}
				else if (dataline[i] == 32)
				{
					i+= 1;
					BRUT +=1;
					FINE +=1;
				}
				
				else if (dataline[i] == 10 || dataline[i] == 13)
				{
					break;
				}

				else
				{
					BRUT ++;
					FINE ++;
					i++;
				}
			}
			FINE +=2; //ajout des double quote en début et fin de ligne 
			printf("BRUT = %d\tFINE = %d\n\n",BRUT,FINE);
			cumulBRUT += BRUT; 
			BRUT= 0;
			cumulFINE +=FINE;
			FINE = 0;
		}	

	printf("cBRUT = %d\ncFINE = %d\n",cumulBRUT,cumulFINE);
	printf("RESULTAT = %d",cumulFINE-cumulBRUT);

	break;
	}

	return 0;
}


