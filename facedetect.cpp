/*
cmake_minimum_required(VERSION 2.8)
project(face_detect)
set(raspicam_DIR "/usr/local/lib/cmake")
find_package(raspicam REQUIRED)
find_package(OpenCV REQUIRED)
add_executable(facedetect facedetect.cpp)
target_link_libraries(facedetect ${OpenCV_LIBS} ${raspicam_CV_LIBS})

*/
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "raspicam/raspicam_cv.h"
 
#include <iostream>
#include <stdio.h>
 
using namespace std;
using namespace cv;
 
int main( )
{
    Mat image;
    raspicam::RaspiCam_Cv Camera;
    Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 );
    Camera.set ( CV_CAP_PROP_FRAME_WIDTH,   256 );
    Camera.set ( CV_CAP_PROP_FRAME_HEIGHT,   256 );
    namedWindow( "Detected Face", 1 );
 
    // Load Face cascade (.xml file)
    CascadeClassifier face_cascade;
    face_cascade.load( "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt2.xml" );
 
    // Detected faces vector
    std::vector<Rect> faces;
    
	cout<<"Connecting to camera"<<endl;
    if ( !Camera.open() ) {
        cerr<<"Error opening camera"<<endl;
        return -1;
    }
    cout<<"Connected to camera ="<<Camera.getId() <<endl;
    cout<<"Capturing"<<endl;

    for (;;) {
        Camera.grab();
        Camera.retrieve ( image );
        // Detet faces
        face_cascade.detectMultiScale( image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
        // Draw circles on the detected faces
		for( int i = 0; i < faces.size(); i++ )
		{
			Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
			ellipse( image, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
		}
		
        imshow( "Detected Face", image );                   // Show our image inside it.
        if (waitKey(30) > 0 ) break;
    }
  
  
  Camera.release();
  
     
    
  return 0;
}
