/* --- Day 11: Corporate Policy ---  

Santa's previous password expired, and he needs help choosing a new one.  

To help him remember his new password after the old one expires, Santa has
devised a method of coming up with a password based on the previous one. 
Corporate policy dictates that passwords must be exactly eight lowercase
letters (for security reasons), so he finds his new password by 
incrementing his old password string repeatedly until it is valid.  

Incrementing is just like counting with numbers: xx, xy, xz, ya, yb, and so on.
Increase the rightmost letter one step; if it was z, it wraps around to a,
and repeat with the next letter to the left until one doesn't wrap around.

Unfortunately for Santa, a new Security-Elf recently started, 
and he has imposed some additional password requirements:
 - Passwords must include one increasing straight of at least three letters,
   like abc, bcd, cde, and so on, up to xyz. They cannot skip letters; abd doesn't count.
 - Passwords may not contain the letters i, o, or l, as these letters 
   can be mistaken for other characters and are therefore confusing.
   Passwords must contain at least two different, non-overlapping pairs 
   of letters, like aa, bb, or zz.  
   
For example:
 - hijklmmn meets the first requirement (because it contains the straight hij)
   but fails the second requirement requirement (because it contains i and l).
 - abbceffg meets the third requirement (because it repeats bb and ff) but 
   fails the first requirement.
 - abbcegjk fails the third requirement, because it only has one double letter (bb).

 The next password after abcdefgh is abcdffaa.
 The next password after ghijklmn is ghjaabcc, because you eventually skip all 
 the passwords that start with ghi..., since i is not allowed.  
 
 Given Santa's current password (your puzzle input), what should his next password be?

 */

#include <stdio.h>
#include <string.h>

int iterateString(char *str)
{
	int i = 0;
	while(1)
	{
		if (*(str+(strlen(str)-1-i)) < 'z')
		{
	//		printf("iteration ++\n");
			*(str+(strlen(str)-1-i)) += 1;
			break;
		}
		else
		{
	//		printf("iteration boucle\n");
			*(str+strlen(str)-1-i) = 'a';
			i++;
		}
	}
	return 0;
}

int verifyPasswordValidity(char *str)
{
	//i,o,l interdits
	int i = 0;
	int niol = 1;

	while(*(str+i) !='\0')
	{
		if (*(str+i) == 'i' || *(str+i) == 'o' || *(str+i) == 'l')
		{
			niol = 0;
		}
		i++;
	}
	
	//double paire nécessaire
	i = 0;
	int doubleFound = 0;
	
	while(*(str+i) !='\0')
	{
		if(*(str+i) == *(str+i+1))
		{
			doubleFound += 1;
			i++;
		}
		i++;
	}

	//suite croissante
	i = 0;
	int suiteCroissante = 0;
	while(*(str+i) != '\0')
	{
		if (*(str+i+2) == *(str+i+1)+1 && *(str+i+1) == *(str+i)+1)
		{
			suiteCroissante += 1;
		}
		i++;
	}

	//conclusion sur la validité return -> 1 si invalide, 0 si valide
	//if (niol) printf("niol OK\t");
	//if (doubleFound >=2) printf("double OK\t");
	if (suiteCroissante) printf("suite OK\t");
	//printf("\n");

	if (doubleFound >=2 && suiteCroissante && niol)
	{
		printf("password valide\n");
		return 0;
	}
	else
	{
		return 1;
	}

	


}


int main(int argc, char *argv[])
{
	//part 1 
	//char input[] = "hxbxwxba";
	//
	
	//part 2
	char input[] = "hxbxxyzz";	
	iterateString(input);	
	//
	
	printf("%s\n",input);

	while(verifyPasswordValidity(input))
	{
		iterateString(input);
	//	printf("suite = %s\n",input);
	}
	printf("suite = %s\n",input);

	return 0;
}

