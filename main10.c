/* --- Day 10: Elves Look, Elves Say ---

Today, the Elves are playing a game called look-and-say.
They take turns making sequences by reading aloud the previous sequence and using that reading as the next sequence.
For example, 211 is read as "one two, two ones", which becomes 1221 (1 2, 2 1s).  
Look-and-say sequences are generated iteratively, using the previous value as input for the next step. 
For each step, take the previous value, and replace each run of digits (like 111) with the number of digits (3) followed by the digit itself (1).
For example:      
1 becomes 11 (1 copy of digit 1).
11 becomes 21 (2 copies of digit 1).
21 becomes 1211 (one 2 followed by one 1).
1211 becomes 111221 (one 1, one 2, and two 1s).
111221 becomes 312211 (three 1s, two 2s, and one 1).

Starting with the digits in your puzzle input, apply this process 40 times. What is the length of the result? */

#include <stdio.h>
#include <string.h>

int x = 1;
	char data[10000000] = "1113222113\0"; 	// Le passage en variable globale permet d'accéder à plus de mémoire
	char test[10000000] = "\0";		// ceci permet d'accéder à la deuxième partie du test.

void lookandsay(char *strout,char *strin)
{
	int i = 0;
	int j = 0;
	int compteur = 0;
	
	while(strin[i] != '\0')
	{		
		//printf("strin[%d] = %c\t strin[%d] = %c\n",i,strin[i],i+1,strin[i+1]);
		if (strin[i+1] == strin[i])
		{
			compteur+=1;
			i++;
			//printf("OK\n");
		}
		else
		{
			strout[j] = compteur+1+'0';
			strout[j+1] = strin[i];
			j = j+2;
			i = i+1;
			compteur = 0;
		}
		//printf("chiffre courant : %c\n",strout[i]);
	}
	strout[j] = '\0';
}

		



int main(int argc, char *argv[])
{
	int x = 0;

	for (x = 0; x < 50;x++)
	{
		printf("x = %d\n",x);
		lookandsay(test,data);
		strcpy(data,test);
		//printf("%s\n",data);
	}

	printf("final = %d\n",strlen(test));


	return 0;

}


