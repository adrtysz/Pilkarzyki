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

int DetectLines(Mat src, const char* sourceName, const char* destName){

	Mat dst, cdst;
	Mat zapisz, pers;
	zapisz = imread("wzor.jpg",0);
	pers = perspective(zapisz);

	
	
	Canny(src, dst, 50, 200, 3);
	cvtColor(dst, cdst, COLOR_GRAY2BGR);
	

	vector<Vec4i> lines;

	HoughLinesP(dst, lines, 1, CV_PI / 180, 20, 10, 5);
	
	for (size_t i = 0; i < 2; i++)
	{
		Vec4i l = lines[i];
		line(pers, Point(l[0]+110, l[1]+180), Point(l[2]+110, l[3]+180), Scalar(0, 0, 255), 3, 2);
	}

	imshow(destName, pers);

	return 0;
}

int main(int argc, char** argv){

	obraz = imread("wzor.jpg", 0);
	//imshow("oryginal", obraz);
	wyjscie = perspective(obraz); //nasz wzor planszy

	ruch = imread("r1.jpg", 0);
	Mat ruch_stary = imread("ruchnowy3.jpg", 0);
	
	wyjscie2 = perspective(ruch);

	


	Mat roi = wyjscie2(Rect(110, 180,130, 130));
	imshow("ROI", roi);
	//Mat roi2 = wyjscie3(Rect(100, 200, 130, 130));

	//Mat test;
	//absdiff(wyjscie3, wyjscie2, test);

	
	//imshow("a", test);
	DetectLines(roi, "line src", "line dest");
	//imwrite("diff.jpg", test);
	waitKey();






	return 0;
	
}

