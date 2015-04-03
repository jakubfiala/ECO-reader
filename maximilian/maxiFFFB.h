//
//  maxiFFFB
//  A formant filter bank similar to the Max/MSP [ffb~] object
//  Created by Jakub Fiala on 21/03/2015.
//

#ifndef __ECO_reader__maxiFFFB__
#define __ECO_reader__maxiFFFB__

#include <stdio.h>
#include <vector>
#include "maximilian.h"

class maxiFFFB {
    int numFilters;
    double output;
    double outputs[10];
    maxiFilter filters[10]; //maximum number of filters
    
public:
    maxiFFFB(int numFormants);
    ~maxiFFFB();
    
    //process and output everything together
    double process(double in, double* freqs, double* qs, double* gains);
    
    //process and output a pointer to individual filter outputs
    double* processIndividual(double in, double* freqs, double* qs, double* gains);
};

#endif /* defined(__ECO_reader__maxiFFFB__) */
