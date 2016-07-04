#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int MAX_KERNEL_LENGTH = 21;
Mat source, g_source, b_source, t_source;
Mat frame, g_frame, b_frame, t_frame;
Mat output, t_output, h_output;
Mat shape, canny_output;
vector<Vec4i> hierarchy;
vector<vector<Point> > contours;

RNG rng(12345);
int dilation_elem = 4;
int dilation_size = 13;

int main(int argc, char* argv[])
{
    double timestamp = (double)clock()/CLOCKS_PER_SEC;
    //VideoCapture cap(0); 
    
    VideoCapture cap("temp.mp4"); 

    if (!cap.isOpened())  
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

   double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
   double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
   namedWindow("MyVideo",CV_WINDOW_AUTOSIZE);
    
    while (1)
    {
	
   	cap.read(source);
    	cvtColor( source, g_source, CV_BGR2GRAY );
    	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
		GaussianBlur( g_source, b_source, Size( i, i ), 0, 0 );

        cap.read(frame);
	cvtColor( frame, g_frame, CV_BGR2GRAY );

        for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
	    GaussianBlur( g_frame, b_frame, Size( i, i ), 0, 0 );

	output = b_source - b_frame;

	Mat element = getStructuringElement( MORPH_RECT,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );

	dilate(output, output, element);
  	threshold( output, output, 10, 255,3);

	Canny( output, canny_output, 13, 22, 3 );
  	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  	vector<vector<Point> > contours_poly( contours.size() );
  	vector<Rect> boundRect( contours.size() );

  	for( int i = 0; i < contours.size(); i++ )
    	 { 
	    approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( Mat(contours_poly[i]) );
     	}


  	Mat drawing = Mat::zeros(output.size(), CV_8UC3 );
  	for( int i = 0; i< contours.size(); i++ )
     	{
            Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
	    if( contours[i].size() > 35)
                rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
     	}

	output = frame + drawing;
        imshow("MyVideo", output); 

        if (waitKey(30) == 27) 
       {
            break; 
       }
    }
    return 0;

}
