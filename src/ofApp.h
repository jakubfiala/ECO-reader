#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxMaxim.h"
#include <iostream>
#include <vector>

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
        void audioRequested(float * output, int bufferSize, int nChannels);
        void audioReceived(float * input, int bufferSize, int nChannels);
    
        //Zhang-Suen test
        void thinningIteration(cv::Mat& im, int iter);
        void thinning(cv::Mat& im);
    
        //T. Monkman stuff
        double pointDistanceFromLine(vector<int> v1, vector<int> v2, vector<int> point);
    

    
    ofVideoGrabber 		vidGrabber;
    ofxCvColorImage     colorImg;
    ofImage             img;
    ofxCvGrayscaleImage gsImg;
    ofxCvContourFinder  contourFinder;
    unsigned char * 	videoInverted;
    ofTexture			videoTexture;
    int 				camWidth;
    int 				camHeight;
    vector<vector<int> > points;
    vector<double>         distances;
    double              bufferPosition;
    double              outputs[2];
    cv::Mat inmat;
    
    maxiSample audioPlayer;
    maxiMix mix;
		
};
