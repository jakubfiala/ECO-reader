// TAR_reader
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
        vidGrabber.setDeviceID(1); //try to select the secondary camera

    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(camWidth,camHeight);

    osc.setup(8320);

    ofSetVerticalSync(true);

    gsImg.allocate(640, 480);

    maxiSettings::sampleRate = 44100;

    position = 0;

    stream.listDevices();
    stream.setDeviceID(4);

    stream.setup(this, 4, 0, 44100, 512, 4);

    stream.start();

}

//--------------------------------------------------------------
void ofApp::update(){
    while(osc.hasWaitingMessages()) {
        ofxOscMessage m;
        osc.getNextMessage(&m);
        env.trigger(0, envdata[0]);
        cout << m.getArgAsString(0) << endl;
    }

    vidGrabber.update();
    if (vidGrabber.isFrameNew()){
        ofPixels pixels;

        //work with the data
        pixels = vidGrabber.getPixelsRef();
        pixels = pixels.getChannel(1); //EXTRACT THE GREEN CHANNEL, IT'S BETTER Ð this should be mentioned in thesis
        gsImg.setFromPixels(pixels);

        for (int i = 0; i < pixels.size(); i++){
            if (pixels[i] > 150) pixels[i] = pixels[i];
            else pixels[i] = 0;
        }

        gsImg.setFromPixels(pixels);
        inmat = toCv(pixels);

        blobToline(inmat);
        //only do this if we're detecting a line
        if (!points.empty()) {
            printf("points size %lu \n", points.size());
            mins.clear();
            maxs.clear();
            distances.clear();
            peaks.clear();

            double maxDistance = 0.0;
            double minDistance = 1000.0;


            for (int i = 0; i < points.size(); i++) {
                distances.push_back((float)pointDistanceFromLine(points[0], points[points.size()-1], points[i]));
            }

            points.clear();

        }

    }


}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 150);
    ofBackground(0);
    vidGrabber.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    double out;

    for (int i = 0; i < bufferSize; i++){
        //play samples
        if (!distances.empty())
        {

            out = (amp.atanDist(distances[(long)position], 500)*0.8 + noise.noise()*0.2) * env.line(8, envdata); //distort and mix in noise, scale by envelope
            position+=0.3; //slow down by 30%
            if (position > distances.size()) position = 0;
        }
        else out = 0;

        output[i*nChannels    ] = out;//left output
        output[i*nChannels + 1] = out;//right output

    }
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels) {

}

//written by Tom Monkman (get a website Tom!)
double ofApp::pointDistanceFromLine(cv::Point2i v1, cv::Point2i v2, cv::Point2i point)
{
    int x1 = v1.x;
    int y1 = v1.y;
    int x2 = v2.x;
    int y2 = v2.y;
    int pointX = point.x;
    int pointY = point.y;
    //Takes a line from 2 points (x1,y1/x2,y2) then works out the perpendicular distance to another point (pointX,pointY) and returns it.
    //http://mathworld.wolfram.com/Point-LineDistance2-Dimensional.html

    return (((x2 - x1)*(y1 - pointY)) - ((x1 - pointX)*(y2 - y1))) / (sqrt((double)((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1))));
}

void ofApp::blobToline(cv::Mat &src)
{
    //OK so this function makes some assumstions, being that:
    //The line will always be vertical, however it can lean, so a diagoal line would be fine, but I think a U shape would not work

    distanceTransform = cv::Mat::zeros(src.size(), CV_32FC1);//Must be a floating point image

    cv::distanceTransform(src, distanceTransform, CV_DIST_L2, 5);//This creates a skeleton like image
    cv::normalize(distanceTransform, distanceTransform, 0.0, 1.0, 32);//This scales the whole image so that its between 0.0 and 1.0
    unsigned int MyX = distanceTransform.cols;
    unsigned int MyY = distanceTransform.rows;
    float* p_distanceTransform = (float*)distanceTransform.data;//Pointers are faster

    //find the start and end of the line
    cv::Point2i startPoint, endPoint;
    for (unsigned int i = MyX; i < MyX * MyY - MyX; i++)//We can loop though the mat as if it is a 1 dimermisional array, this is faster than 2 for loops and using x and y
    {
        if (p_distanceTransform[i] > 0)//See if the pixel either side of the current pixel are lower, if they are, we have found a peak
        {
            //Top of blob found, record the position
            startPoint.x = i % distanceTransform.cols;
            startPoint.y = i / distanceTransform.cols;
            break;//Now we can move on to the next part
        }
    }
    for (unsigned int i = MyX * MyY - MyX; i > 0; i--)//We can loop though the mat as if it is a 1 dimermisional array, this is faster than 2 for loops and using x and y
    {
        if (p_distanceTransform[i] > 0)//See if the pixel either side of the current pixel are lower, if they are, we have found a peak
        {
            //Top of blob found, record the position
            endPoint.x = i % distanceTransform.cols;
            endPoint.y = i / distanceTransform.cols;
            break;//Now we can move on to the next part
        }
    }

    for (unsigned int y = startPoint.y; y < endPoint.y; y++)
    {
        float highest = 0;
        unsigned int position = 0;
        for (unsigned int i = y * MyX; i < (y * MyX) + MyX; i++)
        {
            if (p_distanceTransform[i] > highest)
            {
                highest = p_distanceTransform[i];
                position = i;
            }
        }
        //Record the position found
        cv::Point2i foundPoint;
        foundPoint.x = position % distanceTransform.cols;
        foundPoint.y = position / distanceTransform.cols;
        points.push_back(foundPoint);
    }

}


void ofApp::exit() {
    distances.clear();
    points.clear();
    stream.stop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //env.trigger(0, envdata[0]);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    /*if (x > 0 && y > 0) {
        efreq1 = ofMap(x, 0, ofGetWidth(), 300, 8000);
    }*/

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


