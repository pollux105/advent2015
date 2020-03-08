#include <stdio.h>

void main(){
	
	FILE *data2read;
	
	data2read = fopen("data.txt","r");
	char c;
	int dim1 = 0;
	int dim2 = 0;
	int dim3 = 0;
	int surfa,surfb,surfc;
	int surface = 0;
	int surplus = 0;
	int ligne = 0;
	int surface_temp = 0;
	int ruban = 0;
	printf("debut lecture \n");

	if (data2read)
	{
		while((fscanf(data2read,"%dx%dx%d",&dim1,&dim2,&dim3))!=EOF)
		{
			surfa = dim1*dim2;
			surfb = dim1*dim3;
			surfc = dim2*dim3;

			if (surfa <= surfb)
			{
				if (surfa <= surfc)
				{
					surplus = surfa;
					ruban += (dim1+dim2)*2;
				}
				else
				{
					surplus = surfc;
					ruban += (dim2+dim3)*2;
				}
			}
			else 
			{
				if (surfb <= surfc)
				{
					surplus = surfb;
					ruban += (dim1+dim3)*2;
				}
				else
				{
					surplus = surfc;
					ruban += (dim2+dim3)*2;
				}
			}

			surface_temp =  2 * surfa + 2 * surfb + 2 * surfc + surplus;
			ruban += dim1*dim2*dim3;
			surface = surface + surface_temp;
			ligne +=1;
			printf("ligne n° %d\t %d\t %d\t %d\t surface_temp = %d\t surface = %d\t ruban = %d\n",ligne,dim1,dim2,dim3,surface_temp,surface,ruban);

				
		
		
		}
		printf("surface totale à commander : %d\n",surface);
		printf("longueur totale de ruban à commander : %d\n",ruban);
	}

	
	else 
	{
		printf("probleme de lecture des donnees entrantes");
	}


}

