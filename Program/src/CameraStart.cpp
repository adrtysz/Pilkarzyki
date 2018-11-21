#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;


cv::Mat camera(){

	Mat frame;
	Mat picture;
	char key;
	VideoCapture cap(0);
	for (int i = 0; (i <= 2 && cap.isOpened()); i++)
	{
		cap >> frame;
		frame.copyTo(picture);
		imwrite("photo.jpg", picture);
		return picture;
		if (char(waitKey(30)) == 'q')
			break;
	}
	return picture;
}

