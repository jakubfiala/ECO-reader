#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxMaxim.h"
#include "persistence1d.hpp"
#include "lingua.h"
#include <iostream>
#include <vector>

using namespace p1d;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        //maximilian stuff
        void audioOut(float * output, int bufferSize, int nChannels);
        void audioIn(float * input, int bufferSize, int nChannels);
    
        //T. Monkman stuff
        void blobToline(cv::Mat &src);
        double pointDistanceFromLine(cv::Point2i v1, cv::Point2i v2, cv::Point2i point);
    

    
    ofVideoGrabber 		vidGrabber;
    ofxCvGrayscaleImage gsImg;
    int 				camWidth;
    int 				camHeight;
    vector<cv::Point2i> points;
    vector<float>       distances;
    vector<int>         mins, maxs, peaks;
    double              outputs[2];
    cv::Mat inmat,distanceTransform,dTToShow;
    Persistence1D persist;
    int prevsign;
    
    Lingua lingua;
    
    //synth
    maxiOsc osc;
    double freq;
    double targetfreq;
    
    //formant filterbank Ð add a maxiFFFB object?
    maxiFFFB filterbank  = *new maxiFFFB(5);
    
    double efreqs[5] = {400, 1700, 2600, 3200, 3580};
    double eqs[5]    = {0.6, 0.6, 0.6, 0.6, 0.6};
    double egains[5] = {0.6, 0.1, 0.1, 0.01, 0.001585};
    
    double ifreqs[5] = {270, 2140, 2950, 3900, 4950};
    double iqs[5]    = {0.6, 0.6, 0.6, 0.6, 0.6};
    double igains[5] = {1.0, 0.251189, 0.050119, 0.050119, 0.00631};
    
    double ofreqs[5] = {450, 800, 2830, 3800, 4950};
    double oqs[5]    = {0.6, 0.6, 0.6, 0.6, 0.6};
    double ogains[5] = {1.0, 0.281838, 0.079433, 0.079433, 0.003162};
    
    int vowel;
    
};
