#ifndef _MY_EA_
#define _MY_EA_

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<float.h>
#include<stdbool.h>
#include<math.h>

/* AE Parameters */
#define MAX_CYCLES 1000
#define MAX_POPULATION 5
#define MAX_SELECTED 5
#define MUTATION_FACTOR 2

/* General Parameters */
#define DATA_TYPE double
#define DATA_TYPE_MIN (-1)*FLT_MAX
#define DATA_TYPE_MAX FLT_MAX
#define DEBUG 0

/* Function Parameters */
/* f(x, y) = x^2 - y*/
/* f(x) = 3*x^2*/
// f(x) = x*sin(10*pi*x) +1
#define PARAM_QTY 1    // REMEMBER:::: Change the limits on main code!

typedef struct
{
    DATA_TYPE **dot;
    DATA_TYPE highest, lowest;
    DATA_TYPE paramLimits[PARAM_QTY];
    int qty;
    int param_qty;
}population;


/**
 * @brief Population will be created based on parameters
 * @param n - number of beens of population
 * @return population data structure itsef
 */
population *createPopulation(int, DATA_TYPE *);

void plotPopulation(population *);
void plotSelection(int *);

/**
 * @brief initPopulation
 * @param P
 */
void initPopulation(population *);

/**
 * @brief evalPopulation
 * @param P
 */
void evalPopulation(population *);

/**
 * @brief selection
 * @param P
 * @param S
 */
void selection(population *, int *);

/**
 * @brief isListed
 * @param List
 * @param id
 * @return
 */
bool isListed(int *, int);

/**
 * @brief insertList
 * @param List
 * @param id
 */
void insertList(int *, int);

/**
 * @brief mutation
 * @param P
 * @param S
 */
void mutation(population *, int *);

/**
 * @brief randf
 * @return
 */
float randf(int, int);

/**
 * @brief Clear the entire population
 * @param P - Dataset of the population
 */
void freePopulation(population *);

#endif
