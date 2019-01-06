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

int planszaruch = 0;

int x = 160; //punkt początkowy
int y = 240;

int xRoi = 100;
int yRoi = 180;

Point punkt = Point(160, 240);

int DetectLines(Mat src, const char* sourceName, const char* destName) {


	Mat dst, cdst;
	int direction;
		
	Mat pers = imread("plansza.jpg", 1);

	Mat roi = src(Rect(xRoi, yRoi, 120, 120));
	imshow("roi", roi);

	Canny(roi, dst, 50, 100, 3);
	vector<Vec4i> lines;

	HoughLinesP(dst, lines, 1, CV_PI / 180, 10, 10, 15);

	//threshold: The minimum number of intersections to “detect” a line
	//minLinLength: The minimum number of points that can form a line.Lines with less than this number of points are disregarded.
	//maxLineGap : The maximum gap between two points to be considered in the same line.


	for (size_t i = 0; i < 1; i++) {

		Vec4i l = lines[i];
		
		int roznicax1 = x - (l[0] + xRoi);
		int roznicax2 = x - (l[2] + xRoi);
		int roznicay1 = y - (l[1] + yRoi);
		int roznicay2 = y - (l[3] + yRoi);


		if ((((roznicay1 > 30) && (roznicay1 < 50))) && ((roznicax1 < 10) && (roznicax1 > -10)) || (((roznicay2 > 30) && (roznicay2 < 50))) && ((roznicax2 < 10) && (roznicax2 > -10))) {

			line(pers, Point(punkt.x, punkt.y), Point(punkt.x, punkt.y - 40), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> NORTH << ";
				xRoi = xRoi;
				yRoi = yRoi - 40;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x, punkt.y - 40);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl;

			x = punkt.x;
			y = punkt.y;

			
		

			direction = 4;
		}






		else if ((((roznicay1 > -50) && (roznicay1 < -30))) && ((roznicax1 < 10) && (roznicax1 > -10)) || (((roznicay2 > -50) && (roznicay2 < -30))) && ((roznicax2 < 10) && (roznicax2 > -10))) {


			line(pers, punkt, Point(punkt.x, punkt.y + 40), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> SOUTH << ";
			xRoi = xRoi;
			yRoi = yRoi + 40;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x, punkt.y + 40);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl;

			x = punkt.x;
			y = punkt.y;
		
		}





		else if ((((roznicay1 > -10) && (roznicay1 < 10))) && ((roznicax1 < -30) && (roznicax1 > -50)) || (((roznicay2 > -10) && (roznicay2 < 10))) && ((roznicax2 < -30) && (roznicax2 > -50))) {

			line(pers, punkt, Point(punkt.x + 40, punkt.y), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> EAST<< ";
			xRoi = xRoi+40;
			yRoi = yRoi;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x+40, punkt.y);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl;

			x = punkt.x;
			y = punkt.y;
		}





		else if ((((roznicay1 > -10) && (roznicay1 < 10))) && ((roznicax1 < 50) && (roznicax1 > 30)) || (((roznicay2 > -10) && (roznicay2 < 10))) && ((roznicax2 < 50) && (roznicax2 > 30))) {


			line(pers, punkt, Point(punkt.x - 40, punkt.y), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> WEST << ";
			xRoi = xRoi-40;
			yRoi = yRoi;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x-40, punkt.y);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl;

			
			x = punkt.x;
			y = punkt.y;

		}





		else if ((((roznicay1 > 30) && (roznicay1 < 50))) && ((roznicax1 < -30) && (roznicax1 > -50)) || (((roznicay2 > 30) && (roznicay2 < 50))) && ((roznicax2 < -30) && (roznicax2 > -50))) {


			line(pers, punkt, Point(punkt.x + 40, punkt.y - 40), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> NORTH - EAST << ";
			xRoi = xRoi+40;
			yRoi = yRoi - 40;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x+40, punkt.y - 40);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl;

			x = punkt.x;
			y = punkt.y;

		}




		else if ((((roznicay1 > 30) && (roznicay1 < 50))) && ((roznicax1 < 50) && (roznicax1 > 30)) || (((roznicay2 > 30) && (roznicay2 < 50))) && ((roznicax2 < 50) && (roznicax2 > 30))) {

	 
			line(pers, punkt, Point(punkt.x - 40, punkt.y - 40), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> NORTH - WEST << ";
			xRoi = xRoi - 40;
			yRoi = yRoi - 40;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x - 40, punkt.y - 40);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl;
			
			
			x = punkt.x;
			y = punkt.y;


		}




		else if ((((roznicay1 > -50) && (roznicay1 < -30))) && ((roznicax1 < 50) && (roznicax1 > 30)) || (((roznicay2 > -50) && (roznicay2 < -30))) && ((roznicax2 < 50) && (roznicax2 > 30))) {



			line(pers, punkt, Point(punkt.x - 40, punkt.y + 40), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> SOUTH - WEST << ";
			xRoi = xRoi -40;
			yRoi = yRoi +40;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x-40, punkt.y + 40);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl;


			x = punkt.x;
			y = punkt.y;
		

		}







		else if ((((roznicay1 > -50) && (roznicay1 < -30))) && ((roznicax1 < -30) && (roznicax1 > -50)) || (((roznicay2 > -50) && (roznicay2 < -30))) && ((roznicax2 < -30) && (roznicax2 > -50))) {


			line(pers, punkt, Point(punkt.x + 40, punkt.y + 40), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> SOUTH - EAST<< ";
			xRoi = xRoi+40;
			yRoi = yRoi + 40;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x+40, punkt.y +40);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl;

			x = punkt.x;
			y = punkt.y;

		}


	}




	planszaruch++;
	imshow(destName, pers);
	imwrite("plansza.jpg", pers);

	return 0;
}

int main(int argc, char** argv) { //PAMIETAC O TYM ZEBY PRZEROBIC ROI BO WYCHODZI POZA ZAKRES!!!!!!!!
	Mat zdj_old;
	Mat zdjecie;
	Mat pers_old;
	Mat pers_new;
	Mat pers;
	Mat diff;
	Mat nowa_plansza;

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

	while (1)
	{
		Mat frame;

		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess)
		{
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
				DetectLines(diff, "test", "test");
			}
			else {
				//imshow("zdj", zdj);
				pers = perspective(zdj);
				//imshow("ssss", pers);
				DetectLines(pers, "test", "test");
				//waitKey(0);
			}
		}


	}
	waitKey(0);

	

}
