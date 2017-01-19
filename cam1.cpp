#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int MAX_KERNEL_LENGTH = 21;
Mat source, g_source, b_source, t_source;
Mat frame, g_frame, b_frame, t_frame;
Mat output, t_output;
Mat shape, canny_output;
vector<Vec4i> hierarchy;
vector<vector<Point> > contours;

RNG rng(12345);
int dilation_elem = 4;
int dilation_size = 13;
double alfa =0;

Mat temp[2];

int  counter =0;


Mat frameDifference(Mat A, Mat 😎
{
  Mat diff = abs(A - 😎,
          binaryA,
          binaryB,
          binaryAND;

  threshold(A, binaryA, 0, 256, THRESH_BINARY);
  threshold(B, binaryB, 0, 256, THRESH_BINARY);
  bitwise_and(binaryA, binaryB, binaryAND);
  bitwise_and(diff, binaryAND, diff);

  return diff;
}


int main(int argc, char* argv[])
{

    double timestamp = (double)clock()/CLOCKS_PER_SEC;
    
    VideoCapture cap("temp.mp4"); 

    if (!cap.isOpened())  
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

   double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
   double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
   //namedWindow("MyVideo",CV_WINDOW_AUTOSIZE);
    
    
    cap.read(temp[0]);
 
    

    while (1)
    {
	
	counter++;

	alfa = 2/(counter+0.3);

	cap.read(frame);

        temp[1] = alfa*frame+(1-alfa)*temp[0];  
	

        //imshow("MyVideo", temp[1]); 

	temp[0] = temp[1];
	
	if(counter>120)
		counter = 40;




	cvtColor( temp[0], g_source, CV_BGR2GRAY );

	cvtColor( frame, g_frame, CV_BGR2GRAY );

	output = frameDifference(g_source, g_frame);
	threshold( output, output, 10, 140,3);

	imshow("Treshold3", output);



       if (waitKey(30) == 27) 
       {
            break; 
       }
    
    }
    return 0;

}
