//
//  lingua.h
//  ECO_reader
//
//  Created by Jakub Fiala on 06/01/2015.
//
//

#ifndef __ECO_reader__lingua__
#define __ECO_reader__lingua__

#include <stdio.h>
#include <vector>
#include <cmath>

using namespace std;

class Sign {
public:
    struct peak {
        int level;
    };
    Sign(vector<peak> p);
    Sign(int n);
    int peakCount;
    bool compareAgainst(Sign s);
    vector<peak> peaks;
    
};

class Lingua {
public:
    Lingua();
    vector<Sign> signs;
};



#endif /* defined(__ECO_reader__lingua__) */
