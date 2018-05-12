/*
RaspberryPi 3 B+ w/ Pi Camera v2 OpenCV video stream using raspicam lib
Sammy Hasan
May 2018
*/

#include<stdlib.h>
#include<unistd.h>
#include<iostream>
#include<opencv2/opencv.hpp>
#include "raspicam/raspicam_cv.h"

using namespace std;
using namespace cv;

int main(int argc,char** argv){

  raspicam::RaspiCam_Cv Camera;
  Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3 );
  Camera.set ( CV_CAP_PROP_FRAME_WIDTH,   256 );
  Camera.set ( CV_CAP_PROP_FRAME_HEIGHT,   256 );

  cout<<"Connecting to camera"<<endl;
    if ( !Camera.open() ) {
        cerr<<"Error opening camera"<<endl;
        return -1;
    }
    cout<<"Connected to camera ="<<Camera.getId() <<endl;
    cv::Mat image;
    cout<<"Capturing"<<endl;
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    for (;;) {
        Camera.grab();
        Camera.retrieve ( image );
        imshow( "Display window", image );                   // Show our image inside it.
        if (waitKey(30) > 0 ) break;
    }
  Camera.release();
  return 0;
}
