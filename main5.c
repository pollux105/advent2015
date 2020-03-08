#include <stdio.h>
#include <string.h>

int main(){
	FILE *data2read;
	char lastline[20];
	int compteur = 0;
	
	data2read = fopen("data5.txt","r");

	if(data2read)
	{
		while (fgets(lastline,20,data2read) != NULL)
		{
			printf("caractère en cours %s\n",lastline);
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

