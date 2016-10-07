#include "myEA.h"

population *createPopulation(int n, DATA_TYPE *maxParam)
{
    population *p = (population *)malloc(sizeof(population));
    p->dot = (DATA_TYPE**)malloc(n*sizeof(DATA_TYPE*));
    int i;
    for(i=0; i<n; i++)
    {
        p->dot[i] = malloc((PARAM_QTY+1)*sizeof(DATA_TYPE));
    }

    // Copy The Parameters //
    for(i=0; i<PARAM_QTY; i++)    {p->paramLimits[i] = maxParam[i];}
    p->highest = p->lowest = 0;
    p->qty = n;
    p->param_qty = PARAM_QTY;
}

void initPopulation(population *P)
{
    int i, j;

    // Generate the seed
    srand(time(NULL));

    for(i=0; i<P->qty; i++)
    {
        for(j=0; j<PARAM_QTY; j++)
        {
            //P->dot[i][j] = ((DATA_TYPE)(rand()%((int)P->paramLimits[j])));
            P->dot[i][j] = randf(P->paramLimits[j], 5);
        }
    }
}

void evalPopulation(population *P)
{
    int i, j;
    for(i=0; i<P->qty; i++)
    {   
        //P->dot[i][PARAM_QTY] = (DATA_TYPE)((P->dot[i][0]*P->dot[i][0]) - P->dot[i][1]); /* f(x, y) = x^2 - y*/
        //P->dot[i][PARAM_QTY] = (DATA_TYPE)((3*P->dot[i][0]*P->dot[i][0])); /* f(x, y) = 3*x^2*/
        P->dot[i][PARAM_QTY] = (DATA_TYPE)(P->dot[i][0]*sin(10*P->dot[i][0]*M_PI*10)+1); // f(x) = x*sin(10*pi*x) +1
    }
}

void plotPopulation(population *P)
{
    int i, j;
    for(i=0; i<P->qty; i++)
    {
        printf("P[%d]\t( ", i);
        for(j=0; j<PARAM_QTY; j++)
        {
            printf("%f ", P->dot[i][j]);
        }
        printf(") = %f\n", P->dot[i][PARAM_QTY]);
    }
}

void plotSelection(int *L)
{
    int i;
    printf("Selection: ");
    for(i=0; i<MAX_SELECTED; i++)
    {
        printf("[%d]", L[i]);
    }
    printf("\n");
}

void selection(population *P, int *S)
{
    int i, n, j, nbiggest;
    float biggest;

    /* Clear the List */
    for(i=0; i<MAX_SELECTED; i++)   {S[i] = -1;}

    for(i=0; i<MAX_SELECTED; i++)
    {
        biggest = DATA_TYPE_MIN;
        nbiggest = -1;
        for(n=0; n < P->qty; n++)
        {
            if(!isListed(S, n))
            {
                if(P->dot[n][PARAM_QTY] > biggest)
                {
                    nbiggest = n;
                    biggest = P->dot[n][PARAM_QTY];
                }
            }
        }
        insertList(S, nbiggest);
    }
}

bool isListed(int *List, int id)
{
    int i;
    for(i=0; i<MAX_SELECTED; i++)
    {
        if(List[i] == id){return true;}
    }
    return false;
}

void insertList(int *List, int id)
{
    int i;
    for(i=0; i<MAX_SELECTED; i++)
    {
        if(List[i] == -1)
        {
            List[i]= id;
            return;
        }
    }
}

void mutation(population *P, int *S)
{
    int i, j;
    DATA_TYPE media[PARAM_QTY];

    // Clear the Media Variable
    for(i=0; i<PARAM_QTY; i++)  {media[i] = 0;}

    // Calculates the Medium value //
    for(i=0; i<P->qty; i++)
    {
        if(isListed(S, i))
        {
            for(j=0; j<PARAM_QTY; j++)
            {
                media[j] += P->dot[i][j];
            }
        }
    }
    for(i=0; i<PARAM_QTY; i++)  {media[i] /= P->qty;}

    // Makes the mutation  --> Simply Makes a random value multiplied by the parameters//

    DATA_TYPE aux, aux2;
    for(i=0; i<P->qty; i++)
    {
        if(!isListed(S, i))
        {
            for(j=0; j<PARAM_QTY; j++)
            {
                aux2 = randf(MUTATION_FACTOR, 5);

                aux = media[j]*aux2;

                // Verify if the new parameters are inside the module limits aux < |P|//
                if(aux > 0){
                    while(aux > P->paramLimits[j])  {aux /= 10;}
                }
                else{
                    while(aux < (-1)*P->paramLimits[j])  {aux /= 10;}
                }
                P->dot[i][j] = aux;
            }
        }
    }
}

float randf(int intRange, int length)
{
    int i;

    float acc = (float) (rand()%(intRange));
    int signal = rand()%2;
    for(i=0; i<length; i++)
    {
        acc += (float)(rand()%(10))/(pow(10, i+1));;
    }
    if(!signal){acc*=-1;}
    return acc;
}


void freePopulation(population *P)
{
    int i;
    for(i=0; i<P->qty; i++)
    {
        free(P->dot[i]);
    }
    free(P->dot);
    free(P);
}
