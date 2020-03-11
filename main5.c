/* --- Day 5: Doesn't He Have Intern-Elves For This? ---

Santa needs help figuring out which strings in his text file are naughty or nice.

A nice string is one with all of the following properties:

    It contains at least three vowels (aeiou only), like aei, xazegov, or aeiouaeiouaeiou.
    It contains at least one letter that appears twice in a row, like xx, abcdde (dd), or aabbccdd (aa, bb, cc, or dd).
    It does not contain the strings ab, cd, pq, or xy, even if they are part of one of the other requirements.

For example:

    ugknbfddgicrmopn is nice because it has at least three vowels (u...i...o...), a double letter (...dd...), and none of the disallowed substrings.
    aaa is nice because it has at least three vowels and a double letter, even though the letters used by different rules overlap.
    jchzalrnumimnmhp is naughty because it has no double letter.
    haegwjzuvuyypxyu is naughty because it contains the string xy.
    dvszwmarrgswjxmb is naughty because it contains only one vowel.

How many strings are nice?

--- Part Two ---

Realizing the error of his ways, Santa has switched to a better model of determining whether a string is naughty or nice. 
None of the old rules apply, as they are all clearly ridiculous.

Now, a nice string is one with all of the following properties:

    It contains a pair of any two letters that appears at least twice in the string without overlapping, 
    like xyxy (xy) or aabcdefgaa (aa), but not like aaa (aa, but it overlaps).
    It contains at least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe), or even aaa.

For example:

    qjhvhtzxzqqjkmpb is nice because is has a pair that appears twice (qj) and a letter that repeats with exactly one letter between them (zxz).
    xxyxx is nice because it has a pair that appears twice and a letter that repeats with one between, even though the letters used by each rule overlap.
    uurcxstgmygtbstg is naughty because it has a pair (tg) but no repeat with a single letter between them.
    ieodomkazucvgmuy is naughty because it has a repeating letter with one between (odo), but no pair that appears twice.

How many strings are nice under these new rules?
*/


#include <stdio.h>
#include <string.h>

#define PART1 1
#define PART2 2

int main(int argc, char * argv[] ){
	FILE *data2read;
	char lastline[20];
	int compteur = 0;
	int threeVowels = 0;
	int consecutiveChars = 0;
	int vowelsCount = 0;
	int stringForbidden = 0;
	int i = 0;
	int j = 0;
	int doubleChar = 0;
	int doubleCouple = 0;
	int part;
	printf("%s",argv[1]);
	if (!strcmp(argv[1],"part1"))
	{
		printf("DAY 5 Partie 1\n");
		part = PART1;
	}
	else
	{
		printf("DAY 5 Partie 2\n");
		part = PART2;
	}



	data2read = fopen("data5.txt","r");

	switch(part)
	{
		case PART1 :

		if(data2read)
		{
			while (fgets(lastline,20,data2read) != NULL)
			{
				for (i = 0; lastline[i]!='\0'; i++)
				{	
					if (lastline[i+1] == lastline[i])
					{
						consecutiveChars = 1;
					}	
				}
	
/*				if (consecutiveChars == 0) {printf("CChars BAD\t");}
				else {printf("CChars OK\t");}
	
*/	
				for (j = 0;lastline[j]!='\0';j++)
				{
					if (lastline[j] == 'a' || lastline[j] == 'e' || \
					lastline[j] == 'i' || lastline[j] == 'o' || \
					lastline[j] == 'u')
					{
						vowelsCount +=1;
					}
				}
	

				if (vowelsCount >= 3) 
				{
					threeVowels = 1;
					//printf("Vowels OK\t");
				}
				else
				{
					//printf("Vowels BAD\t");
					//printf("%d\t %s",compteur,lastline);
				}
	
				vowelsCount = 0;
	
				
				if ((strstr(lastline,"ab") != NULL) 
							|| (strstr(lastline,"cd") != NULL) \
							|| (strstr(lastline,"pq") != NULL)\
							|| (strstr(lastline,"xy") != NULL))
				{
					stringForbidden = 1;
					//printf("Expression interdite\t");
				}
				else
				{ 
					stringForbidden = 0;
					//printf("Expression OK   \t");
				}
	
	
				if (!stringForbidden && consecutiveChars && threeVowels)
				{
					compteur++;
					//printf("Ligne Valide\t%s",lastline);
				}
	
				else
				{
					//printf("Mauvaise ligne\t%s",lastline);
				}	

				threeVowels = 0;
				consecutiveChars = 0;
				stringForbidden = 0;
			}
		}

		else
		{
			printf("fichier introuvable\n");
			return 255;
		}
		
		printf("compteur = %d\n",compteur);
		return 0;
		break;


		case(PART2):
		
		if(data2read)
		{
			while (fgets(lastline,20,data2read) != NULL)
			{
				for (i = 0;lastline[i] != '\0'; i++)
				{
					if (lastline[i+2] == lastline[i])
					{
						doubleChar = 1;
						break;
					}
				}
				if (doubleChar)
				{
					for (i = 0;lastline[i+3] != '\0' ; i++)
					{
						for (j = i+2; lastline[j+1] != '\0' ; j++)
						{
							if (strncmp(lastline+i,lastline+j,2) == 0)
							{
								doubleCouple = 1;
								break;
							}

						}
						if (doubleCouple) break;
					}
				}

				if (doubleCouple && doubleChar) 
				{
					compteur++;
					//printf("OK\t%s",lastline);
				}
				else
				{
					//printf("BAD\t%s",lastline);
				}

			doubleChar = doubleCouple = 0;

			}


		}
	
		else
		{
			printf("fichier illisible\n");
		}

		printf("Résultat : %d\n",compteur);

		return 0;
		break;
	}
	return 0;
}

