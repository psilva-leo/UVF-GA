#include "utils.h"

double Utils::randf(int max, int min) {
    int i;
    double acc;
    int signal = rand()%2;

    // Negative
    if(!signal) {
        acc = (double) (rand()%((int)min));
        acc*=-1;
    }

    // Positive
    if(signal) {
        acc = (double) (rand()%((int)max));
    }

    // Precision
    for(i=0; i<FRAND_PRECISION; i++) {
        acc += (double)(rand()%(10))/(pow(10, i+1));;
    }
    if(!signal && acc<min){acc = min;}
    else if(signal && acc>max){acc = max;}

    return acc;
}
