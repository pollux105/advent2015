#include <stdio.h>


void main(){

	printf("START-UP\n");
	char c;
	FILE *file2read;
	int i = 0, pos = 0;


	if (file2read = fopen("data.txt","r"))
	{

		while (c != EOF && i >= 0)
		{
			c = getc(file2read);
			pos +=1;
			if (c==40) i+=1;
			else if (c==41) i-=1;
			printf ("valeur de c : %d\t valeur de i : %d\tpos : %d\n",c,i,pos);

		}
	}

	else
	{
		printf("probleme d'ouverture du fichier");
	}
	printf("hauteur %d",i);
}
