#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "FindContours.h"


using namespace cv;
using namespace std;

Mat src1; 


/** @function main */
int main(int argc, char** argv)
{
	/// Load source image and convert it to gray
	src1 = imread(argv[1], 1);

	load(src1);
	//dzia³aj¹ca kamerka, póki co w mainie, do przeniesienia do przetwarzania obrazów +- tydzieñ 
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "change the camera port number! ";
		return -1;
	}
	while (true)
	{
		Mat frame;
		cap.read(frame);
		imshow("camera", frame);
		if (waitKey(30) == 27)
		{
			return 0;
		}
	}








	// Convert image to gray and blur it
	//cvtColor(src, src_gray, CV_BGR2GRAY);


	/*if (src.empty())
		cout << "gunwo";
	else if (src.channels() > 1)
		cvtColor(src, src_gray, CV_BGR2GRAY);
	else src_gray = src; 
	
	blur(src_gray, src_gray, Size(3, 3));

	/// Create Window
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);

	waitKey(0); 
	return(0); */
}


