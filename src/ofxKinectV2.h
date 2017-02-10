//
//  ofxKinectV2.h
//  kinectExample
//
//  Created by Theodore Watson on 6/23/14.
//
//

#pragma once

#include "ofProtonect.h"
#include "ofMain.h"

class ofxKinectV2 : public ofThread{

    public:
    
        libfreenect2::Freenect2 freenect2;
        libfreenect2::Registration* registration;

        struct KinectDeviceInfo{
            string serial;
            int deviceId;   //if you have the same devices plugged in device 0 will always be the same Kinect
            int freenectId; //don't use this one - this is the index given by freenect2 - but this can change based on order device is plugged in
        };

        ofxKinectV2();
        ~ofxKinectV2(); 
        
        //for some reason these can't be static - so you need to make a tmp object to query them
        vector <KinectDeviceInfo> getDeviceList();
        unsigned int getNumDevices();
    
        bool open(string serial);
        bool open(unsigned int deviceId = 0);
        void update();
        void close();
    
        bool isFrameNew();
    
        ofPixels getDepthPixels();
        void* getDepthFrame();
        ofPixels getRgbPixels();
        void* getRgbFrame();
        ofFloatPixels getRawDepthPixels();
    
        ofParameterGroup params;
        ofParameter <float> minDistance;
        ofParameter <float> maxDistance;

    protected:
        void threadedFunction();

        ofPixels rgbPix;
        ofPixels depthPix;
        ofFloatPixels rawDepthPixels;
    
        bool bNewBuffer;
        bool bNewFrame;
        bool bOpened;
    
        ofProtonect protonect;
    
        ofPixels rgbPixelsBack;
        ofPixels rgbPixelsFront;
        libfreenect2::Frame *rgbFrame;
        libfreenect2::Frame *depthFrame;


        ofFloatPixels depthPixelsBack;
        ofFloatPixels depthPixelsFront;
        int lastFrameNo; 
};