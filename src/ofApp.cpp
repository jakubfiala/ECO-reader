// ECO_reader
// oF implementation of structured light scanning (laser line)
// by Jakub Fiala ||| http://fiala.uk
// for the Ex Caelis Oblata project http://excaelisoblata.tumblr.com/
// developed at Goldsmiths, London
// 2014


#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    camWidth 		= 640;	// try to grab at this size.
    camHeight 		= 480;
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
    }
    
    if (devices.size() == 1)
        vidGrabber.setDeviceID(0);
    else
        vidGrabber.setDeviceID(1); //always select the secondary camera
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(camWidth,camHeight);
    
    videoInverted 	= new unsigned char[camWidth*camHeight*3];
    videoTexture.allocate(camWidth,camHeight, GL_RGB);
    ofSetVerticalSync(true);
    
    colorImg.allocate(640, 480);
    gsImg.allocate(640, 480);
    img.allocate(640, 480, OF_IMAGE_GRAYSCALE);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(100,100,100);
    
    vidGrabber.update();
    ofPixels pixels;
    
    if (vidGrabber.isFrameNew()){
        
        //work with the data
        colorImg.setFromPixels(vidGrabber.getPixelsRef());
        gsImg = colorImg;
        pixels = gsImg.getPixelsRef();
        for (int i = 0; i < pixels.size(); i++){
            if (pixels[i] > 215) pixels[i] = pixels[i];
            else pixels[i] = 1;
        }
        gsImg.setFromPixels(pixels);
        
        inmat = toCv(pixels);

        
        thinning(inmat);
        //only do this if we're detecting a line
        if (points.size() > 0) {
            double maxDistance = 0.0;
            double minDistance = 1000.0;
            
            //normalize to -1, 1 (because we're not killing the soundcard are we?
            for (int i = 0; i < points.size(); i++) {
                distances.push_back(pointDistanceFromLine(points[0], points[points.size()-1], points[i]));
                if (distances[i] > maxDistance) {
                    maxDistance = distances[i];
                }
                if (distances[i] < minDistance) {
                    minDistance = distances[i];
                }
            }
            
            for (int i = 0; i < points.size(); i++) {
                distances[i] = (distances[i]-minDistance)/(maxDistance-minDistance) * 2 - 1;
                printf("%f ", distances[i]);
            }
            
            
            //printf("%f %f \n\n", minDistance, maxDistance);
            printf("\n\n");
        }
        
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xffffff);
    ofSetColor(255, 150);
    //gsImg.draw(0, 0, camWidth, camHeight);
    drawMat(inmat, 0, 0);
}

void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels)
{
    for (int i = 0; i < bufferSize; i++)
    {
        double out = audioPlayer.jfBufferPlay(distances, distances.size());

        mix.stereo(out, outputs, 0.5);
        
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];
    }
}

void ofApp::audioReceived 	(float * input, int bufferSize, int nChannels)
{
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


//Zhang-Suen thinning algorithm
//T. Y. Zhang and C. Y. Suen. 1984. A fast parallel algorithm for thinning digital patterns. Commun. ACM 27, 3 (March 1984), 236-239. DOI=10.1145/357994.358023 http://doi.acm.org/10.1145/357994.358023
//just awesome.

/**
 * Perform one thinning iteration.
 * Normally you wouldn't call this function directly from your code.
 *
 * @param  im    Binary image with range = 0-1
 * @param  iter  0=even, 1=odd
 */
void ofApp::thinningIteration(cv::Mat& im, int iter)
{
    points.clear();

    cv::Mat marker = cv::Mat::zeros(im.size(), CV_8UC1);
    
    for (int i = 1; i < im.rows-1; i++)
    {
        for (int j = 1; j < im.cols-1; j++)
        {
            uchar p2 = im.at<uchar>(i-1, j);
            uchar p3 = im.at<uchar>(i-1, j+1);
            uchar p4 = im.at<uchar>(i, j+1);
            uchar p5 = im.at<uchar>(i+1, j+1);
            uchar p6 = im.at<uchar>(i+1, j);
            uchar p7 = im.at<uchar>(i+1, j-1);
            uchar p8 = im.at<uchar>(i, j-1);
            uchar p9 = im.at<uchar>(i-1, j-1);
            
            int A  = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
            (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
            (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
            (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
            int B  = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
            int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
            int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);
            
            if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
            {
                marker.at<uchar>(i,j) = 1;
                vector<int> pt;
                pt.push_back(i);
                pt.push_back(j);
                points.push_back(pt);
            }
        }
    }

    im &= ~marker;
}

/**
 * Function for thinning the given binary image
 *
 * @param  im  Binary image with range = 0-255
 */
void ofApp::thinning(cv::Mat& im)
{
    im /= 255;
    
    cv::Mat prev = cv::Mat::zeros(im.size(), CV_8UC1);
    cv::Mat diff;
    
    do {
        thinningIteration(im, 0);
        thinningIteration(im, 1);
        cv::absdiff(im, prev, diff);
        im.copyTo(prev);
    }
    while (cv::countNonZero(diff) > 0);
    
    im *= 255;
}


//written by Tom Monkman (get a website Tom!)
double ofApp::pointDistanceFromLine(vector<int> v1, vector<int> v2, vector<int> point)
{
    int x1 = v1[0];
    int y1 = v1[1];
    int x2 = v2[0];
    int y2 = v2[1];
    int pointX = point[0];
    int pointY = point[1];
    //Takes a line from 2 points (x1,y1/x2,y2) then works out the perpendicular distance to another point (pointX,pointY) and returns it.
    //http://mathworld.wolfram.com/Point-LineDistance2-Dimensional.html
    
    return (((x2 - x1)*(y1 - pointY)) - ((x1 - pointX)*(y2 - y1))) / (sqrt((double)((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1))));
}
