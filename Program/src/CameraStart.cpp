#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;


cv::Mat camera(){

VideoCapture cap(0);
	//xD
	/*if (!cap.isOpened())
	{
		cout << "change the camera port number! ";
		return frame;
	}*/
	while (true)
	{
		//cout << "cos";
		Mat frame;
		cap.read(frame);
		imshow("camera", frame);
		if (waitKey(30) == 27)
		{
			return frame;
		}
		return frame;
	}
}

