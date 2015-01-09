//
//  lingua.cpp
//  ECO_reader
//
//  Created by Jakub Fiala on 06/01/2015.
//
//

#include "lingua.h"

using namespace std;

//Sign methods
Sign::Sign(int n) {
    peakCount = n;
}

bool Sign::compareAgainst(Sign s) {
    if (s.peakCount == peakCount)
    {
        return true;
    }
    else
    {
        return false;
    }
}


Lingua::Lingua() {
    signs.push_back(*new Sign(1));
    signs.push_back(*new Sign(2));
    signs.push_back(*new Sign(3));
}