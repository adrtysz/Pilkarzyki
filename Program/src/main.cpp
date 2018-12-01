#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "FindContours.h"
#include "Contours.h"
#include "CameraStart.h"
#include "Perspective.h"

using namespace cv;
using namespace std;

Mat obraz;
Mat wyjscie;
Mat ruch;
Mat wyjscie2;

int DetectLines(Mat src, const char* sourceName, const char* destName)
{


	Mat dst, cdst;
	Mat zapisz;
	zapisz = imread("plansza3.jpg",0);
	
	Canny(src, dst, 50, 200, 3);
	cvtColor(dst, cdst, COLOR_GRAY2BGR);
	

	vector<Vec4i> lines;

	HoughLinesP(dst, lines, 1, CV_PI / 180,20,10, 3);
	
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(zapisz, Point(l[0]+115, l[1]+188), Point(l[2]+115, l[3]+188), Scalar(0, 0, 255), 3, 2);
	}


	//imshow(sourceName, src);
	imshow(destName, zapisz);

	return 0;
}

int main(int argc, char** argv){

	obraz = imread("plansza1.jpg", 0);
	//imshow("oryginal", obraz);
	wyjscie = perspective(obraz);

	ruch = imread("ruch1.jpg", 0);


	wyjscie2 = perspective(ruch);


	


	Mat roi = wyjscie2(Rect(110, 180,130, 130));
	imshow("Example1", roi);
	/*Mat roi = wyjscie2(Rect(80, 180, 130, 130));
	imshow("Example1", roi);*/
	Mat roi2 = wyjscie(Rect(100, 200, 130, 130));


	

	
	imshow("a", roi);
	DetectLines(roi, "line src", "line dest");

	waitKey();






	return 0;
	
}

