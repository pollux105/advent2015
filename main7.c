/*
--- Day 7: Some Assembly Required ---

This year, Santa brought little Bobby Tables a set of wires and bitwise logic gates! 
Unfortunately, little Bobby is a little under the recommended age range, and he needs help assembling the circuit.

Each wire has an identifier (some lowercase letters) and can carry a 16-bit signal (a number from 0 to 65535). 
A signal is provided to each wire by a gate, another wire, or some specific value. Each wire can only get a signal from one source, 
but can provide its signal to multiple destinations. A gate provides no signal until all of its inputs have a signal.

The included instructions booklet describes how to connect the parts together: x AND y -> z means to connect wires x and y to an AND gate,
and then connect its output to wire z.

For example:

    123 -> x means that the signal 123 is provided to wire x.
    x AND y -> z means that the bitwise AND of wire x and wire y is provided to wire z.
    p LSHIFT 2 -> q means that the value from wire p is left-shifted by 2 and then provided to wire q.
    NOT e -> f means that the bitwise complement of the value from wire e is provided to wire f.

Other possible gates include OR (bitwise OR) and RSHIFT (right-shift). 
If, for some reason, you'd like to emulate the circuit instead, 
almost all programming languages (for example, C, JavaScript, or Python) provide operators for these gates.

For example, here is a simple circuit:

123 -> x
456 -> y
x AND y -> d
x OR y -> e
x LSHIFT 2 -> f
y RSHIFT 2 -> g
NOT x -> h
NOT y -> i

After it is run, these are the signals on the wires:

d: 72
e: 507
f: 492
g: 114
h: 65412
i: 65079
x: 123
y: 456

In little Bobby's kit's instructions booklet (provided as your puzzle input), what signal is ultimately provided to wire a?

--- Part Two ---

Now, take the signal you got on wire a, override wire b to that signal, and reset the other wires (including wire a). 
What new signal is ultimately provided to wire a?

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define LEFTHAND 1
#define RIGHTHAND 2

FILE *data2read;
char dataline[50];
char *token;

int marqueurEnsemble = 0;
int pointerID1;
int pointerID2;
int ptrFullCalculation = 1;

fpos_t position = NULL;

typedef struct Wire Wire;
struct Wire
{
	char identifier[5];
	unsigned short signal;
};

struct Wire Ensemble[400];

typedef struct Formula Formula;
struct Formula
{
	char modifier[7];
	char identifier1[5];
	char identifier2[5];
	char wire[5];
};


void formulaReset(Formula* equation2reset);
void calculateWire(Formula* formula, Wire* tableau, int* id1, int* id2);
int dataAvailable(Formula* formula, Wire* tableau, int* id1, int* id2);

void formulaReset(Formula* equation2reset)
{
	strcpy(equation2reset->modifier,"init");
	strcpy(equation2reset->identifier1,"init");
	strcpy(equation2reset->identifier2,"init");
	strcpy(equation2reset->wire,"init");
}

void strip(char *s) {
    char *p2 = s;
    while(*s != '\0') {
        if(*s != '\n') {
            *p2++ = *s++;


        } else {
            ++s;
        }
    }
    *p2 = '\0';
}


int wireUnknown(Formula* formula,Wire* tableau)
{
	int i;
	printf("%s\n",formula->wire);
    for (i=0 ; i<marqueurEnsemble+1; i++)
    {
        if (!strcmp(formula->wire,tableau[i].identifier))
        {
        return 0;
        }
    }
    return 1;
}

int dataAvailable(Formula* formula,Wire* tableau,int *id1, int *id2)
{
	int i,j;
	i =0;
	j=0;

	// MODIFIER = "NOT"

	if (!strcmp(formula->modifier,"NOT"))
	{
		for (i=0; i<marqueurEnsemble+1;i++)
		{
			if(!strcmp(formula->identifier1,tableau[i].identifier))
			{
				*id1 = i;
				return 1;
			}
		}

		return 0;

	}

	// MODIFIER  = "INIT"

	else if (!strcmp(formula->modifier,"init"))
	{
		for (i=0; i<marqueurEnsemble+1;i++)
		{
			if (!strcmp(formula->identifier1,tableau[i].identifier))
			{
				*id1 = 1;
				return 1;
			}
			else if (isdigit(formula->identifier1[0]))
			{
				return 1;
			}
		}

		return 0;

	}

	// MODIFIER = AUTRE

	else
	{
		for (i=0; i<marqueurEnsemble+1;i++)
		{
			if (strcmp(formula->identifier1,tableau[i].identifier) == 0 || isdigit(formula->identifier1[0]))
			{
                for (j=0; j<marqueurEnsemble+1;j++)
				{
                    if (strcmp(formula->identifier2,tableau[j].identifier) == 0 || isdigit(formula->identifier2[0]))
					{
						*id1 = i;
						*id2 = j;
						return 1;
					}
				}
			}
		}

		return 0;
	}
}

void calculateWire(Formula* formula, Wire *tableau, int* ligneE1, int* ligneE2)
{
    int premier_membre;
    int second_membre;
    int i;

    if (isdigit(formula->identifier1[0]))
    {
        premier_membre = atoi(formula->identifier1);
    }
    else
    {
        premier_membre = tableau[*ligneE1].signal;
    }

    if (isdigit(formula->identifier2[0]))
    {
        second_membre = atoi(formula->identifier2);
    }
    else
    {
        second_membre = tableau[*ligneE2].signal;
    }

	if (!strcmp(formula->modifier,"init"))
	{
		if (isdigit(formula->identifier1[0]))
		{
			strcpy(tableau[marqueurEnsemble].identifier,formula->wire);
			tableau[marqueurEnsemble].signal = atoi(formula->identifier1);
		}
		else
		{
			strcpy(tableau[marqueurEnsemble].identifier,formula->wire);
            		for (i = 0; i<marqueurEnsemble; i++)
            		{
                		if (!strcmp(formula->identifier1,tableau[i].identifier))
                		{
                	    		tableau[marqueurEnsemble].signal = tableau[i].signal;
                		}
            		}
		}

	}
	else if (!strcmp(formula->modifier,"NOT"))
	{
		strcpy(tableau[marqueurEnsemble].identifier,formula->wire);
		tableau[marqueurEnsemble].signal = ~premier_membre;
	}
	else if (!strcmp(formula->modifier,"AND"))
	{
		strcpy(tableau[marqueurEnsemble].identifier,formula->wire);
		tableau[marqueurEnsemble].signal = premier_membre & second_membre;
	}
	else if (!strcmp(formula->modifier,"OR"))
	{
		strcpy(tableau[marqueurEnsemble].identifier,formula->wire);
		tableau[marqueurEnsemble].signal = premier_membre | second_membre;

	}
	else if (!strcmp(formula->modifier,"RSHIFT"))
	{
		strcpy(tableau[marqueurEnsemble].identifier,formula->wire);
		tableau[marqueurEnsemble].signal = premier_membre >> second_membre;
	}
	else if (!strcmp(formula->modifier,"LSHIFT"))
	{
		strcpy(tableau[marqueurEnsemble].identifier,formula->wire);
        tableau[marqueurEnsemble].signal = premier_membre << second_membre;
	}
	else
	{
	}

	marqueurEnsemble +=1;

}


int main(int argc,char * argv[] )
{
	int i;
	int uncomplete = 1;
	Formula Equation;
	for (i = 0; i<400;i++)
	{
		strcpy(Ensemble[i].identifier,"ini");
		Ensemble[i].signal = 65535;
	}


	data2read = fopen("C:\\data7.txt","r");

	formulaReset(&Equation);

    while(uncomplete)
    {
        uncomplete = 0;
        rewind(data2read);

        while(fgets(dataline,sizeof(dataline)/sizeof(char),data2read)!= NULL)
        {
            int equation_side = LEFTHAND;

            token = strtok(dataline," ");

            // -------------------
            // COMPOSITION FORMULE
            // -------------------

            while(token !=NULL){

                strip(token);

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
                            }
                        break;

                        case RIGHTHAND:

                            strcpy(Equation.wire,token);

                        break;
                    }
                }
                token = strtok(NULL," ");

            }

            // ------------------------
            // - CALCUL SELON FORMULE -
            // ------------------------

            // déterminer si la formule est calculable
            if (dataAvailable(&Equation,Ensemble,&pointerID1,&pointerID2) && wireUnknown(&Equation,Ensemble))
            {
                calculateWire(&Equation,Ensemble,&pointerID1,&pointerID2);
            }
            else if (wireUnknown(&Equation,Ensemble))
            {
                uncomplete = 1;
            }
            else
            {
            }


            formulaReset(&Equation);


            int k = 0;

        }

    }


	int j = 0;
	int a = 65535;
	while (strcmp(Ensemble[++j].identifier,"ini"))
	{
		printf("identifiant : %s  \tsignal : %d\n",Ensemble[j].identifier,Ensemble[j].signal);
		if (!strcmp(Ensemble[j].identifier,"a")) a = Ensemble[j].signal;
	}

	printf ("\n\na = %d",a);

	return 0;
}



