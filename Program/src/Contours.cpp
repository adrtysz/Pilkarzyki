#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;


cv::Mat loadAndCrop(Mat img0) {

    Mat img1;
    cvtColor(img0, img1, CV_RGB2GRAY);
    Canny(img1, img1, 100, 200);

    vector< vector<Point> > contours;
    findContours(img1, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    Mat mask = Mat::zeros(img1.rows, img1.cols, CV_8UC1);
    drawContours(mask, contours, -1, Scalar(255), CV_FILLED);

   
    Mat crop(img0.rows, img0.cols, CV_8UC3);

    crop.setTo(Scalar(255,255,255));

    img0.copyTo(crop, mask);

   
    normalize(mask.clone(), mask, 0.0, 255.0, CV_MINMAX, CV_8UC1);

    //imshow("cropped", crop);

    imwrite("cropped.jpg", crop);
    
	return crop;
}