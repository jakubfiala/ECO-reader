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
Sign::Sign(vector<peak> p) {
    peakCount = p.size();
    peaks = p;
}

Sign::Sign(int n) {
    peakCount = n;
}

bool Sign::compareAgainst(Sign s) {
    if (s.peaks.size() == peaks.size())
    {
        int remaining = peakCount;
        for (int i = 0; i < s.peaks.size(); i++) {
            if (s.peaks[i].level == peaks[i].level) {
                remaining--;
            }
        }
        if (remaining) return false;
        else return true;
    }
    else
    {
        return false;
    }
}


Lingua::Lingua() {
    printf("setup");
    //BASIC THREE UNILEVEL SIGNS
    //sign 1--------------------------
    vector<Sign::peak> vp1;
    Sign::peak p1_1;
    p1_1.level = 2;
    vp1.push_back(p1_1);
    signs.push_back(*new Sign(vp1));
    
    //sign 2--------------------------
    vector<Sign::peak> vp2;
    Sign::peak p2_1, p2_2;
    p2_1.level = 2;
    p2_2.level = 2;
    vp2.push_back(p2_1);
    vp2.push_back(p2_2);
    signs.push_back(*new Sign(vp2));
    
    //sign 3--------------------------
    vector<Sign::peak> vp3;
    Sign::peak p3_1, p3_2, p3_3;
    p3_1.level = 2;
    p3_2.level = 2;
    p3_3.level = 2;
    vp3.push_back(p3_1);
    vp3.push_back(p3_2);
    vp3.push_back(p3_3);
    signs.push_back(*new Sign(vp3));
    
    //MULTILEVEL SIGNS
    //sign4--------------------------
    vector<Sign::peak> vp4;
    Sign::peak p4_1, p4_2;
    p4_1.level = 1;
    p4_2.level = 2;
    vp4.push_back(p4_1);
    vp4.push_back(p4_2);
    signs.push_back(*new Sign(vp4));
    
}