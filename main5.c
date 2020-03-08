#include <stdio.h>
#include <string.h>

int main(){
	FILE *data2read;
	char lastline[20];
	int compteur = 0;
	int threeVowels = 0;
	int consecutiveChars = 0;
	int vowelsCount = 0;

	data2read = fopen("data5.txt","r");

	if(data2read)
	{
		while (fgets(lastline,20,data2read) != NULL)
		{
			//printf("%s",lastline);


			for (int i = 0; lastline[i]!='\0'; i++)
			{	
				if (lastline[i+1] == lastline[i])
				{
					consecutiveChars = 1;
				}
			}

			if (consecutiveChars == 0)
			{
				//printf("CChars BAD\t");
			}
			else
			{
				//printf("CChars OK\t");
			}



			for (int j = 0;lastline[j]!='\0';j++)
			{
				if (lastline[j] == 'a' || lastline[j] == 'e' || \
				lastline[j] == 'i' || lastline[j] == 'o' || \
				lastline[j] == 'u')
					vowelsCount +=1;
			}

			if (vowelsCount >= 3) 
			{
			
				threeVowels = 1;
				//printf("Vowels OK\t");
			}
			else
			{
				//printf("Vowels BAD\t");
				printf("%d\t %s",compteur,lastline);
			}

			vowelsCount = 0;


			if ((strstr(lastline,"ab") || strstr(lastline,"cd") \
						|| strstr(lastline,"pq") \
						|| strstr(lastline,"xy") == NULL) && \
				threeVowels && consecutiveChars)
			{
				compteur++;
				//printf("OK\n");
				//	break;
			}
			else
				//printf("NOT OK\n");

			threeVowels = 0;
			consecutiveChars = 0;
		}
	}
	else
	{
		printf("fichier introuvable\n");
		return 255;
	}

	printf("compteur = %d\n",compteur);
	return 0;
}

