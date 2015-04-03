
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
    //sign 4--------------------------
    vector<Sign::peak> vp4;
    Sign::peak p4_1, p4_2;
    p4_1.level = 1;
    p4_2.level = 2;
    vp4.push_back(p4_1);
    vp4.push_back(p4_2);
    signs.push_back(*new Sign(vp4));

    //sign 5--------------------------
    vector<Sign::peak> vp5;
    Sign::peak p5_1, p5_2;
    p5_1.level = 2;
    p5_2.level = 1;
    vp5.push_back(p5_1);
    vp5.push_back(p5_2);
    signs.push_back(*new Sign(vp5));

    //sign 6--------------------------
    vector<Sign::peak> vp6;
    Sign::peak p6_1, p6_2, p6_3;
    p6_1.level = 2;
    p6_2.level = 1;
    p6_3.level = 1;
    vp6.push_back(p6_1);
    vp6.push_back(p6_2);
    vp6.push_back(p6_3);
    signs.push_back(*new Sign(vp6));

    //sign 7--------------------------
    vector<Sign::peak> vp7;
    Sign::peak p7_1, p7_2, p7_3;
    p7_1.level = 2;
    p7_2.level = 2;
    p7_3.level = 1;
    vp7.push_back(p7_1);
    vp7.push_back(p7_2);
    vp7.push_back(p7_3);
    signs.push_back(*new Sign(vp7));

    //sign 8--------------------------
    vector<Sign::peak> vp8;
    Sign::peak p8_1, p8_2, p8_3;
    p8_1.level = 2;
    p8_2.level = 1;
    p8_3.level = 2;
    vp8.push_back(p8_1);
    vp8.push_back(p8_2);
    vp8.push_back(p8_3);
    signs.push_back(*new Sign(vp8));

    //sign 9--------------------------
    vector<Sign::peak> vp9;
    Sign::peak p9_1, p9_2, p9_3;
    p9_1.level = 1;
    p9_2.level = 1;
    p9_3.level = 2;
    vp9.push_back(p9_1);
    vp9.push_back(p9_2);
    vp9.push_back(p9_3);
    signs.push_back(*new Sign(vp9));

    //sign 10--------------------------
    vector<Sign::peak> vp10;
    Sign::peak p10_1, p10_2, p10_3;
    p10_1.level = 1;
    p10_2.level = 2;
    p10_3.level = 2;
    vp10.push_back(p10_1);
    vp10.push_back(p10_2);
    vp10.push_back(p10_3);
    signs.push_back(*new Sign(vp10));

    //sign 11--------------------------
    vector<Sign::peak> vp11;
    Sign::peak p11_1, p11_2, p11_3;
    p11_1.level = 1;
    p11_2.level = 2;
    p11_3.level = 1;
    vp11.push_back(p11_1);
    vp11.push_back(p11_2);
    vp11.push_back(p11_3);
    signs.push_back(*new Sign(vp11));

}