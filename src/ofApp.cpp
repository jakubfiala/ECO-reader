// ECO_reader
// oF implementation of structured light scanning (laser line)
// by Jakub Fiala ||| http://fiala.uk
// for the Ex Caelis Oblata project http://excaelisoblata.tumblr.com/
// developed at Goldsmiths, London
// 2014


#include "ofApp.h"

using namespace cv;
using namespace ofxCv;


double sineBuffa[514]={0,0.012268,0.024536,0.036804,0.049042,0.06131,0.073547,0.085785,0.097992,0.1102,0.12241,0.13455,0.1467,0.15884,0.17093,0.18301,0.19507,0.20709,0.21909,0.23105,0.24295,0.25485,0.26669,0.2785,0.29025,0.30197,0.31366,0.32529,0.33685,0.34839,0.35986,0.37128,0.38266,0.39395,0.40521,0.41641,0.42752,0.4386,0.44958,0.46051,0.47137,0.48215,0.49286,0.50351,0.51407,0.52457,0.53497,0.54529,0.55554,0.5657,0.57578,0.58575,0.59567,0.60547,0.6152,0.62482,0.63437,0.6438,0.65314,0.66238,0.67151,0.68057,0.68951,0.69833,0.70706,0.7157,0.72421,0.7326,0.74091,0.74908,0.75717,0.76514,0.77298,0.7807,0.7883,0.79581,0.80316,0.81042,0.81754,0.82455,0.83142,0.8382,0.84482,0.85132,0.8577,0.86392,0.87006,0.87604,0.88187,0.8876,0.89319,0.89862,0.90396,0.90912,0.91415,0.91907,0.92383,0.92847,0.93295,0.93729,0.9415,0.94556,0.94949,0.95325,0.95691,0.96039,0.96375,0.96692,0.97,0.9729,0.97565,0.97827,0.98074,0.98306,0.98523,0.98724,0.98914,0.99084,0.99243,0.99387,0.99515,0.99628,0.99725,0.99808,0.99875,0.99927,0.99966,0.99988,0.99997,0.99988,0.99966,0.99927,0.99875,0.99808,0.99725,0.99628,0.99515,0.99387,0.99243,0.99084,0.98914,0.98724,0.98523,0.98306,0.98074,0.97827,0.97565,0.9729,0.97,0.96692,0.96375,0.96039,0.95691,0.95325,0.94949,0.94556,0.9415,0.93729,0.93295,0.92847,0.92383,0.91907,0.91415,0.90912,0.90396,0.89862,0.89319,0.8876,0.88187,0.87604,0.87006,0.86392,0.8577,0.85132,0.84482,0.8382,0.83142,0.82455,0.81754,0.81042,0.80316,0.79581,0.7883,0.7807,0.77298,0.76514,0.75717,0.74908,0.74091,0.7326,0.72421,0.7157,0.70706,0.69833,0.68951,0.68057,0.67151,0.66238,0.65314,0.6438,0.63437,0.62482,0.6152,0.60547,0.59567,0.58575,0.57578,0.5657,0.55554,0.54529,0.53497,0.52457,0.51407,0.50351,0.49286,0.48215,0.47137,0.46051,0.44958,0.4386,0.42752,0.41641,0.40521,0.39395,0.38266,0.37128,0.35986,0.34839,0.33685,0.32529,0.31366,0.30197,0.29025,0.2785,0.26669,0.25485,0.24295,0.23105,0.21909,0.20709,0.19507,0.18301,0.17093,0.15884,0.1467,0.13455,0.12241,0.1102,0.097992,0.085785,0.073547,0.06131,0.049042,0.036804,0.024536,0.012268,0,-0.012268,-0.024536,-0.036804,-0.049042,-0.06131,-0.073547,-0.085785,-0.097992,-0.1102,-0.12241,-0.13455,-0.1467,-0.15884,-0.17093,-0.18301,-0.19507,-0.20709,-0.21909,-0.23105,-0.24295,-0.25485,-0.26669,-0.2785,-0.29025,-0.30197,-0.31366,-0.32529,-0.33685,-0.34839,-0.35986,-0.37128,-0.38266,-0.39395,-0.40521,-0.41641,-0.42752,-0.4386,-0.44958,-0.46051,-0.47137,-0.48215,-0.49286,-0.50351,-0.51407,-0.52457,-0.53497,-0.54529,-0.55554,-0.5657,-0.57578,-0.58575,-0.59567,-0.60547,-0.6152,-0.62482,-0.63437,-0.6438,-0.65314,-0.66238,-0.67151,-0.68057,-0.68951,-0.69833,-0.70706,-0.7157,-0.72421,-0.7326,-0.74091,-0.74908,-0.75717,-0.76514,-0.77298,-0.7807,-0.7883,-0.79581,-0.80316,-0.81042,-0.81754,-0.82455,-0.83142,-0.8382,-0.84482,-0.85132,-0.8577,-0.86392,-0.87006,-0.87604,-0.88187,-0.8876,-0.89319,-0.89862,-0.90396,-0.90912,-0.91415,-0.91907,-0.92383,-0.92847,-0.93295,-0.93729,-0.9415,-0.94556,-0.94949,-0.95325,-0.95691,-0.96039,-0.96375,-0.96692,-0.97,-0.9729,-0.97565,-0.97827,-0.98074,-0.98306,-0.98523,-0.98724,-0.98914,-0.99084,-0.99243,-0.99387,-0.99515,-0.99628,-0.99725,-0.99808,-0.99875,-0.99927,-0.99966,-0.99988,-0.99997,-0.99988,-0.99966,-0.99927,-0.99875,-0.99808,-0.99725,-0.99628,-0.99515,-0.99387,-0.99243,-0.99084,-0.98914,-0.98724,-0.98523,-0.98306,-0.98074,-0.97827,-0.97565,-0.9729,-0.97,-0.96692,-0.96375,-0.96039,-0.95691,-0.95325,-0.94949,-0.94556,-0.9415,-0.93729,-0.93295,-0.92847,-0.92383,-0.91907,-0.91415,-0.90912,-0.90396,-0.89862,-0.89319,-0.8876,-0.88187,-0.87604,-0.87006,-0.86392,-0.8577,-0.85132,-0.84482,-0.8382,-0.83142,-0.82455,-0.81754,-0.81042,-0.80316,-0.79581,-0.7883,-0.7807,-0.77298,-0.76514,-0.75717,-0.74908,-0.74091,-0.7326,-0.72421,-0.7157,-0.70706,-0.69833,-0.68951,-0.68057,-0.67151,-0.66238,-0.65314,-0.6438,-0.63437,-0.62482,-0.6152,-0.60547,-0.59567,-0.58575,-0.57578,-0.5657,-0.55554,-0.54529,-0.53497,-0.52457,-0.51407,-0.50351,-0.49286,-0.48215,-0.47137,-0.46051,-0.44958,-0.4386,-0.42752,-0.41641,-0.40521,-0.39395,-0.38266,-0.37128,-0.35986,-0.34839,-0.33685,-0.32529,-0.31366,-0.30197,-0.29025,-0.2785,-0.26669,-0.25485,-0.24295,-0.23105,-0.21909,-0.20709,-0.19507,-0.18301,-0.17093,-0.15884,-0.1467,-0.13455,-0.12241,-0.1102,-0.097992,-0.085785,-0.073547,-0.06131,-0.049042,-0.036804,-0.024536,-0.012268,0,0.012268
};



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
    
    ofSetVerticalSync(true);
    
    gsImg.allocate(640, 480);
    
    maxiSettings::sampleRate = 44100;
    
    for (int i = 0; i < 512; i++)
        distances.push_back(sineBuffa[i]);
    
    position = 0;
    
    ofSoundStreamSetup(2,2,this, 44100, 512, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    /*vidGrabber.update();
    if (vidGrabber.isFrameNew()){
        ofPixels pixels;
        
        //work with the data
        pixels = vidGrabber.getPixelsRef();
        pixels = pixels.getChannel(1); //EXTRACT THE GREEN CHANNEL, IT'S BETTER Ð this should be mentioned in thesis
        gsImg.setFromPixels(pixels);
        
        for (int i = 0; i < pixels.size(); i++){
            if (pixels[i] > 250) pixels[i] = pixels[i];
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
                if (i > 1) {
                    //low-pass filter
                    distances[i] -= (distances[i]-distances[i-1])/1.05;// - (distances[i]-distances[i-2])/2;
                }
            }
            
            points.clear();

            /*persist.RunPersistence(distances);
            persist.GetExtremaIndices(mins, maxs, 5.0, false);
            
            Sign sign = *new Sign(maxs.size());
            
            //calculate biggest peak
            double maximumPeakValue = 0;
            int maximumPeak;
            for(int m = 0; m < maxs.size(); m++) {
                if (distances[maxs[m]] > maximumPeakValue) {
                    maximumPeakValue = distances[maxs[m]];
                    maximumPeak = maxs[m];
                }
            }
            
            for(int m = 0; m < maxs.size(); m++) {
                Sign::peak p;
                if (maxs[m] == maximumPeak)
                    p.level = 2;
                else if (distances[maxs[m]]/maximumPeakValue < 0.5) {
                    p.level = 1;
                    //printf("HALF");
                }
                else
                    p.level = 2;
                sign.peaks.push_back(p);
            }
            //printf("peaks: %lu distances: %lu \n", sign.peaks.size(), distances.size());
            for (int l = 0; l < lingua.signs.size(); l++) {
                if (lingua.signs[l].compareAgainst(sign) && l != prevsign) {
                    prevsign = l;
                    printf("found sign: %i with %lu peaks \n", l+1, sign.peaks.size());
                    switch (l+1) {
                        case 1:
                            vowel = 0;
                            break;
                        case 2:
                            vowel = 1;
                            break;
                        case 3:
                            vowel = 2;
                            break;
                        case 4:
                            targetfreq += 2*4;
                            break;
                        case 5:
                            targetfreq += 2*3;
                            break;
                        case 6:
                            targetfreq += 2*2;
                            break;
                        case 7:
                            targetfreq += 2*1;
                            break;
                        case 8:
                            targetfreq -= 2*1;
                            break;
                        case 9:
                            targetfreq -= 2*2;
                            break;
                        case 10:
                            targetfreq -= 2*3;
                            break;
                        case 11:
                            targetfreq -= 2*4;
                            break;
                        default:
                            break;
                    }
                    
                    break;
                }
            }
        }
        
    }*/
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 150);
    ofBackground(0);
    /*vidGrabber.draw(0,0);
    dTToShow = distanceTransform * 255;
    drawMat(dTToShow, 0, 0);
    //gsImg.draw(0, 0, camWidth, camHeight);
    
    //drawMat(inmat, 0, 0);
    for (int i = 0; i < distances.size(); i++) {
        ofRect(i*2, 0, 2, distances[i]);
    }
    ofSetColor(255, 0, 0);
    for (int j = 0; j < maxs.size(); j++) {
        ofRect(maxs[j]*2, 0, 2, distances[maxs[j]]);
    }*/

}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    double out;
    
    for (int i = 0; i < bufferSize; i++){
        //play samples
        if (!distances.empty())
        {
            out = distances[position];
            position++;
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


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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


