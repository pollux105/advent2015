#include <stdio.h>
#include <string.h>

#define LEFTHAND 1
#define RIGHTHAND 2

FILE *data2read;
char dataline[50];
char *token;

typedef struct Wire Wire;
struct Wire
{
	char identifier[3];
	int signal;
};

struct Wire Ensemble[300];

typedef struct Formula Formula;
struct Formula
{
	char modifier[10];
	char identifier1[5];
	char identifier2[5];
	char wire[5];
};


void formulaReset(Formula* equation2reset);
void calculateWire(Formula* formula, Wire* wire);
int dataAvailable(Formula* formula);

void formulaReset(Formula* equation2reset)
{
	strcpy(equation2reset->modifier,"init");
	strcpy(equation2reset->identifier1,"init");
	strcpy(equation2reset->identifier2,"init");	
	strcpy(equation2reset->wire,"init");
}


int dataAvailable(Formula* formula)
{
	int i;
	for (i = 0; i<300; i++)
	{
		if (isdigit(Ensemble[i].identifier) || !strcmp(Ensemble[i].identifier, formula->identifier1))
		{
			printf("identifiant trouvé!");
			return 1;
		}
		
	}

}


void calculateWire(Formula* formula, Wire* wire,int i)
{
	if (!strcmp(formula->modifier))
	{
		if (isdigit(formula->identifier1))
		{
			strcpy(formula->wire,Wire->identifier);
			Wire->signal = atoi(formula->identifier);
			
}






int main(int argc,char * argv[] )
{
	int i;
	Formula Equation;
	for (i = 0; i<300;i++)
	{
		strcpy(Ensemble[i].identifier,"\0");
		Ensemble[i].signal = -1;
	}


	data2read = fopen("data7.txt","r");
	
	formulaReset(&Equation);

	while(fgets(dataline,sizeof(dataline)/sizeof(char),data2read)!= NULL)
	{
		int equation_side = LEFTHAND;
		token = strtok(dataline," ");

		while(token !=NULL){
			printf("%s\n",token);

			if (!strcmp(token,"AND") || !strcmp(token,"OR") || !strcmp(token,"NOT") || !strcmp(token,"LSHIFT") || !strcmp(token,"RSHIFT"))
			{
				strcpy(Equation.modifier,token);
			}
			else if (!strcmp(token,"->"))
			{
				equation_side = RIGHTHAND;
			}
			else
			{
				switch(equation_side)
				{
					case LEFTHAND:

						if (!strcmp(Equation.identifier1,"init"))
						{
							strcpy(Equation.identifier1,token);
						}
						else
						{
							strcpy(Equation.identifier2,token);
							printf("IDENTIFIER 2 !");
						}
					break;

					case RIGHTHAND:

						strcpy(Equation.wire,token);
						printf("\tWIRE : %s\n",Equation.wire);

					break;
				}
			}


			token = strtok(NULL," ");


		}
		
		


		formulaReset(&Equation);
	}

		
		
	int j = 0;
	while (Ensemble[j].signal != -1)
	{
		printf("%s\t%d\n",Ensemble[j].identifier,Ensemble[j].signal);
		j++;
	}
	
	return 0;
}


