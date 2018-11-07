#include "Contours.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int loadAndCut(Mat src) {

	Mat img1;
	cvtColor(src, img1, CV_RGB2GRAY);

	// apply your filter
	Canny(img1, img1, 100, 200);

	// find the contours
	vector< vector<Point> > contours;
	findContours(img1, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	// you could also reuse img1 here
	Mat mask = Mat::zeros(img1.rows, img1.cols, CV_8UC1);

	// CV_FILLED fills the connected components found
	drawContours(mask, contours, -1, Scalar(255), CV_FILLED);

	/*
	 Before drawing all contours you could also decide
	 to only draw the contour of the largest connected component
	 found. Here's some commented out code how to do that:
	*/

	//    vector<double> areas(contours.size());
	//    for(int i = 0; i < contours.size(); i++)
	//        areas[i] = contourArea(Mat(contours[i]));
	//    double max;
	//    Point maxPosition;
	//    minMaxLoc(Mat(areas),0,&max,0,&maxPosition);
	//    drawContours(mask, contours, maxPosition.y, Scalar(1), CV_FILLED);

		// let's create a new image now
	Mat crop(src.rows, src.cols, CV_8UC3);

	// set background to green
	crop.setTo(Scalar(0, 255, 0));

	// and copy the magic apple
	src.copyTo(crop, mask);

	// normalize so imwrite(...)/imshow(...) shows the mask correctly!
	normalize(mask.clone(), mask, 0.0, 255.0, CV_MINMAX, CV_8UC1);

	imwrite("cropped.jpg", crop);
	return 0;



}
