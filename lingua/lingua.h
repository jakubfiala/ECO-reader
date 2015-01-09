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

using namespace std;

class Sign {
public:
    Sign(int n);
    int peakCount;
    struct peak {
        int index;
        int level;
    };
    bool compareAgainst(Sign s);
    vector<peak> peaks;
    
};

class Lingua {
public:
    Lingua();
    vector<Sign> signs;
};



#endif /* defined(__ECO_reader__lingua__) */
