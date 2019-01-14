#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "DetectLine.h"
#include "GetRoi.h"
#include "Winner.h"
#include "Perspective.h"

using namespace cv;
using namespace std;
int planszaruch = 0;



int main(int argc, char** argv) { //PAMIETAC O TYM ZEBY PRZEROBIC ROI BO WYCHODZI POZA ZAKRES!!!!!!!!
	Mat zdj_old;
	Mat zdjecie;
	Mat pers_old;
	Mat pers_new;
	Mat pers;
	Mat diff;
	Mat nowa_plansza;
	Mat zwyciestwo;
	nowa_plansza = imread("new.jpg", 1);
	imwrite("plansza.jpg", nowa_plansza);



	VideoCapture cap(0); // open the video camera no. 0

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);

	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);

	while (1){
		Mat frame;
		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess){
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}
		imshow("MyVideo", frame);

		if (waitKey(30) == 27) {
			cout << "esc key is pressed by user" << endl;
			break;
		}

		else if (waitKey(30) == 32) {

			frame.copyTo(zdjecie);
			if (planszaruch > 0)
			{
				zdj_old = imread("zdjecie1.jpg", 0);
				imwrite("zdjecie0.jpg", zdj_old);
			}
			imwrite("zdjecie1.jpg", zdjecie);


			Mat zdj = imread("zdjecie1.jpg", 0);
			if (planszaruch > 0)
			{
				pers_old = perspective(zdj_old);
				pers_new = perspective(zdj);
				absdiff(pers_old, pers_new, diff);
				imshow("xd", diff);
				DetectLines(diff, "PLANSZA GRY", "PLANSZA GRY");
				planszaruch++;
			}
			else {
				//imshow("zdj", zdj);
				pers = perspective(zdj);
				//imshow("ssss", pers);
				DetectLines(pers, "PLANSZA GRY", "PLANSZA GRY");
				//waitKey(0);
				planszaruch++;

				
				}
			}
		}


	
	waitKey(0);
}