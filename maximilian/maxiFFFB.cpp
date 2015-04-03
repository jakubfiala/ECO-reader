//
//  maxiFFFB
//  A formant filter bank similar to the Max/MSP [fffb~] object
//  Created by Jakub Fiala on 21/03/2015.
//

#include "maxiFFFB.h"

maxiFFFB::maxiFFFB(int numFormants) {
    numFilters = numFormants;
}

maxiFFFB::~maxiFFFB() {
    delete [] &outputs;
    delete [] &filters;
}

double maxiFFFB::process(double in, double *freqs, double *qs, double *gains) {
    
    output = 0.0f;
    
    for (int i = 0; i < numFilters; i++) {
        output += filters[i].formant(in, freqs[i], qs[i], gains[i]);
    }
    
    return output;
}

double* maxiFFFB::processIndividual(double in, double *freqs, double *qs, double *gains) {
    for (int i = 0; i < numFilters; i++) {
        outputs[i] = filters[i].formant(in, freqs[i], qs[i], gains[i]);
    }
    
    return &outputs[0];
}