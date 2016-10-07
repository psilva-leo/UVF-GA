#include<stdio.h>
#include<stdlib.h>
#include "myEA.h"


int main(int argc, char *argv[])
{
    DATA_TYPE paramLimits[PARAM_QTY] = {2};

    population *P;
    P = createPopulation(MAX_POPULATION, paramLimits);

    int selected[MAX_SELECTED];

    /* Initialize Population */
    initPopulation(P);

    srand(time(NULL));

    int cycle;
    for(cycle=0; cycle<MAX_CYCLES; cycle++)
    {
        /* Initial Evaluation */
        evalPopulation(P);
        if(DEBUG)plotPopulation(P);

        selection(P, selected);
        if(DEBUG)plotSelection(selected);

        mutation(P, selected);
    }
    plotPopulation(P);
    plotSelection(selected);

    freePopulation(P);
}
