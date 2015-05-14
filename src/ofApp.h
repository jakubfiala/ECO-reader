#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxMaxim.h"
#include "ofxOsc.h"
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
    
        void exit();
    
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
    vector<double>       distances;
    vector<int>         mins, maxs, peaks;
    double              outputs[2];
    double                 position;
    cv::Mat             inmat,distanceTransform,dTToShow;
    
    ofSoundStream  stream;
    
    ofxOscReceiver osc;
    maxiEnvelope   env;
    maxiDistortion amp;
    maxiOsc        noise;
    
    
    double envdata[8] = {0.9, 50, 0.7, 500, 0.5, 1000, 0.0001, 2000};
    
    int vowel;
    
};
