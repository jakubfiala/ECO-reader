#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
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
        std::vector<std::vector<int> > getLine(cv::Mat image, int threshold);
        vector<double> distanceMetricFromLine(vector<vector<int> > line);
    
        //Guo-Hall test
        void thinningGuoHallIteration(cv::Mat& im, int iter);
        void thinningGuoHall(cv::Mat& im);
    
        //Zhang-Suen test
        void thinningIteration(cv::Mat& im, int iter);
        void thinning(cv::Mat& im);
    

    
    ofVideoGrabber 		vidGrabber;
    ofxCvColorImage     colorImg;
    ofImage             img;
    ofxCvGrayscaleImage gsImg;
    ofxCvContourFinder  contourFinder;
    unsigned char * 	videoInverted;
    ofTexture			videoTexture;
    int 				camWidth;
    int 				camHeight;
    vector<vector<int> > line;
    vector<double> distances;
    cv::Mat inmat;
		
};
