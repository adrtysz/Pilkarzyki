#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "FindContours.h"
#include "Contours.h"
#include "CameraStart.h"


using namespace cv;
using namespace std;

Mat src1; 


/** @function main */
int main(int argc, char** argv)
{
	/// Load source image and convert it to gray
	src1 = imread(argv[1], 1);

	load(src1);
	loadAndCrop(src1);
	camera();
	//dzia�aj�ca kamerka, p�ki co w mainie, do przeniesienia do przetwarzania obraz�w +- tydzie� 
	
	/*VideoCapture cap(0);
	//xD
	if (!cap.isOpened())
	{
		cout << "change the camera port number! ";
		return -1;
	}
	while (true)
	{
		//cout << "cos";
		Mat frame;
		cap.read(frame);
		imshow("camera", frame);
		if (waitKey(30) == 27)
		{
			return 0;
		}

		
	}*/


}


