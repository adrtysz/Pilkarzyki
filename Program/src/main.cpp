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



int DetectLines(Mat src, const char* sourceName, const char* destName) {


	Mat dst, cdst;
	int direction;
		
	Point punkt = Point(160, 240);

	Point punkt_zm;

	Mat pers = imread("plansza.jpg", 1);


	int x = 160; //punkt początkowy
	int y = 240;

	int x1 = 0; //zmienne dla kolejnych punktów
	int y1 = 0;

	int xRoi = 120;
	int yRoi = 200;  //punkty dla ROI

	int xRoi1 = 0; // zmienne dla kolejnych punktow ROI
	int yRoi1 = 0;

	Mat roi = src(Rect(xRoi, yRoi, 100, 100));


	Canny(roi, dst, 50, 200, 3);
	cvtColor(dst, cdst, COLOR_GRAY2BGR);

	vector<Vec4i> lines;

	HoughLinesP(dst, lines, 1, CV_PI / 180, 20, 10, 5);

	for (size_t i = 0; i < 1; i++) {

		Vec4i l = lines[i];
		//line(pers, Point(l[0] + xRoi, l[1] + yRoi), Point(l[2] + xRoi, l[3] + yRoi), Scalar(0, 0, 255), 3, 2);

		//  x1           y1               x2              y2



		cout << "Roznica x2 : " << x - (l[2] + 120) << " \t Roznica x1 : " << x - (l[0] + 120) << endl;
		cout << "Roznica y2 : " << y - (l[3] + 200) << " \t Roznica y1 : " << y - (l[1] + 200) << endl;

		int roznicax1 = x - (l[0] + xRoi);
		int roznicax2 = x - (l[2] + xRoi);
		int roznicay1 = y - (l[1] + yRoi);
		int roznicay2 = y - (l[3] + yRoi);


		if ((((roznicay1 > 20) && (roznicay1 < 50))) && ((roznicax1 < 10) && (roznicax1 > -10)) || (((roznicay2 > 20) && (roznicay2 < 50))) && ((roznicax2 < 10) && (roznicax2 > -10))) {

			if ((roznicay1 > 20) && (roznicay1 < 50)) {
				y1 = y - roznicay1;
				x1 = x + roznicax1;

				xRoi1 = xRoi + roznicax1;
				yRoi1 = yRoi - roznicay1;

				




			}
			else if ((roznicay2 > 20) && (roznicay2 < 50)) {
				y1 = y - roznicay2;
				x1 = x + roznicax2;

				xRoi1 = xRoi + roznicax2;
				yRoi1 = yRoi - roznicay2;
			}
			
			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> NORTH << ";
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "xRoi1 " << xRoi1 << " \t yRoi1 " << yRoi1 << endl;

			line(pers, punkt, Point(punkt.x, punkt.y-40), Scalar(0, 0, 255), 3, 2);
			punkt = Point(punkt.x, punkt.y - 40);

			direction = 4;

			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRAŁ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRAŁ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}




		}






		else if ((((roznicay1 > -50) && (roznicay1 < -20))) && ((roznicax1 < 10) && (roznicax1 > -10)) || (((roznicay2 > -50) && (roznicay2 < -20))) && ((roznicax2 < 10) && (roznicax2 > -10))) {

			if ((roznicay1 > -50) && (roznicay1 < -20)) {
				y1 = y + abs(roznicay1);
				x1 = x + abs(roznicax1);


				xRoi1 = xRoi + abs(roznicax1);
				yRoi1 = yRoi + abs(roznicay1);
			}
			else if ((roznicay2 > -50) && (roznicay2 < -20)) {
				y1 = y + abs(roznicay2);
				x1 = x + abs(roznicax2);

				xRoi1 = xRoi + abs(roznicax2);
				yRoi1 = yRoi + abs(roznicay2);
			}
			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> SOUTH << ";
			direction = 0;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "xRoi1 " << xRoi1 << " \t yRoi1 " << yRoi1 << endl;


			line(pers, punkt, Point(punkt.x, punkt.y + 40), Scalar(0, 0, 255), 3, 2);
			punkt = Point(punkt.x, punkt.y + 40);


			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRAŁ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRAŁ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}





		else if ((((roznicay1 > -10) && (roznicay1 < 10))) && ((roznicax1 < -20) && (roznicax1 > -50)) || (((roznicay2 > -10) && (roznicay2 < 10))) && ((roznicax2 < -20) && (roznicax2 > -50))) {

			if ((roznicax1 < -20) && (roznicax1 > -50)) {

				x1 = x + abs(roznicax1);
				y1 = y + abs(roznicay1);


				xRoi1 = xRoi + abs(roznicax1);
				yRoi1 = yRoi + abs(roznicay1);

			}

			else if ((roznicax2 < -20) && (roznicax2 > -50)) {
				x1 = x + abs(roznicax2);
				y1 = y + abs(roznicay2);

				xRoi1 = xRoi + abs(roznicax2);
				yRoi1 = yRoi + abs(roznicay2);
			}

			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> EAST << ";
			direction = 2;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "xRoi1 " << xRoi1 << " \t yRoi1 " << yRoi1 << endl;

			line(pers, punkt, Point(punkt.x+40, punkt.y), Scalar(0, 0, 255), 3, 2);
			punkt = Point(punkt.x+40, punkt.y);

			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRAŁ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRAŁ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}





		else if ((((roznicay1 > -10) && (roznicay1 < 10))) && ((roznicax1 < 50) && (roznicax1 > 20)) || (((roznicay2 > -10) && (roznicay2 < 10))) && ((roznicax2 < 50) && (roznicax2 > 20))) {

			if ((roznicax1 < 50) && (roznicax1 > 20)) {

				x1 = x - abs(roznicax1);
				y1 = y + abs(roznicay1);

				xRoi1 = xRoi - abs(roznicax1);
				yRoi1 = yRoi + abs(roznicay1);

			}

			else if ((roznicax2 < 50) && (roznicax2 > 20)) {
				x1 = x - abs(roznicax2);
				y1 = y + abs(roznicay2);

				xRoi1 = xRoi - abs(roznicax2);
				yRoi1 = yRoi + abs(roznicay2);
			}

			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> WEST << ";
			direction = 6;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "xRoi1 " << xRoi1 << " \t yRoi1 " << yRoi1 << endl;


			line(pers, punkt, Point(punkt.x - 40, punkt.y), Scalar(0, 0, 255), 3, 2);
			punkt = Point(punkt.x - 40, punkt.y);

			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRAŁ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRAŁ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}





		else if ((((roznicay1 > 20) && (roznicay1 < 50))) && ((roznicax1 < -20) && (roznicax1 > -50)) || (((roznicay2 > 20) && (roznicay2 < 50))) && ((roznicax2 < -20) && (roznicax2 > -50))) {

			if ((roznicay1 > 20) && (roznicay1 < 50) && (roznicax1 < -20) && (roznicax1 > -50)) {

				y1 = y - abs(roznicay1);
				x1 = x + abs(roznicax1);

				xRoi1 = xRoi + abs(roznicax1);
				yRoi1 = yRoi - abs(roznicay1);

			}
			else if ((roznicay2 > 20) && (roznicay2 < 50) && (roznicax2 < -20) && (roznicax2 > -50)) {

				y1 = y - abs(roznicay2);
				x1 = x + abs(roznicax2);

				xRoi1 = xRoi + abs(roznicax2);
				yRoi1 = yRoi - abs(roznicay2);


			}

			line(pers, punkt, Point(punkt.x + 40, punkt.y-40), Scalar(0, 0, 255), 3, 2);
			punkt = Point(punkt.x + 40, punkt.y-40);

			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> NORTH - EAST << ";
			direction = 3;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "xRoi1 " << xRoi1 << " \t yRoi1 " << yRoi1 << endl;

			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRAŁ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRAŁ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}




		else if ((((roznicay1 > 20) && (roznicay1 < 50))) && ((roznicax1 < 50) && (roznicax1 > 20)) || (((roznicay2 > 20) && (roznicay2 < 50))) && ((roznicax2 < 50) && (roznicax2 > 20))) {

			if ((roznicay1 > 20) && (roznicay1 < 50) && (roznicax1 < 50) && (roznicax1 > 20)) {

				y1 = y - abs(roznicay1);
				x1 = x - abs(roznicax1);

				xRoi1 = xRoi - abs(roznicax1);
				yRoi1 = yRoi - abs(roznicay1);

			}
			else if ((roznicay2 > 20) && (roznicay2 < 50) && (roznicax2 < 50) && (roznicax2 > 20)) {

				y1 = y - abs(roznicay2);
				x1 = x - abs(roznicax2);

				xRoi1 = xRoi - abs(roznicax2);
				yRoi1 = yRoi - abs(roznicay2);
			}



			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> NORTH - WEST << ";
			direction = 5;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "xRoi1 " << xRoi1 << " \t yRoi1 " << yRoi1 << endl;

			line(pers, punkt, Point(punkt.x - 40, punkt.y - 40), Scalar(0, 0, 255), 3, 2);
			punkt = Point(punkt.x - 40, punkt.y - 40);


			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRAŁ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRAŁ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}




		else if ((((roznicay1 > -50) && (roznicay1 < -20))) && ((roznicax1 < 50) && (roznicax1 > 20)) || (((roznicay2 > -50) && (roznicay2 < -20))) && ((roznicax2 < 50) && (roznicax2 > 20))) {


			if ((roznicay1 > -50) && (roznicay1 < -20) && (roznicax1 < 50) && (roznicax1 > 20)) {

				y1 = y + abs(roznicay1);
				x1 = x - abs(roznicax1);


				xRoi1 = xRoi - abs(roznicax1);
				yRoi1 = yRoi + abs(roznicay1);

			}

			else if ((roznicay2 > -50) && (roznicay2 < -20) && (roznicax2 < 50) && (roznicax2 > 20)) {

				y1 = y + abs(roznicay2);
				x1 = x - abs(roznicax2);


				xRoi1 = xRoi - abs(roznicax2);
				yRoi1 = yRoi + abs(roznicay2);

			}


			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> SOUTH - WEST << ";
			direction = 7;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "xRoi1 " << xRoi1 << " \t yRoi1 " << yRoi1 << endl;

			line(pers, punkt, Point(punkt.x - 40, punkt.y + 40), Scalar(0, 0, 255), 3, 2);
			punkt = Point(punkt.x - 40, punkt.y + 40);

			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRAŁ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRAŁ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}







		else if ((((roznicay1 > -50) && (roznicay1 < -20))) && ((roznicax1 < -20) && (roznicax1 > -50)) || (((roznicay2 > -50) && (roznicay2 < -20))) && ((roznicax2 < -20) && (roznicax2 > -50))) {


			if ((roznicay1 > -50) && (roznicay1 < -20) && (roznicax1 < -20) && (roznicax1 > -50)) {

				y1 = y + abs(roznicay1);
				x1 = x + abs(roznicax1);

				xRoi1 = xRoi + abs(roznicax1);
				yRoi1 = yRoi + abs(roznicay1);

			}

			else if ((roznicay2 > -50) && (roznicay2 < -20) && (roznicax2 < -20) && (roznicax2 > -50)) {

				y1 = y + abs(roznicay2);
				x1 = x + abs(roznicax2);

				xRoi1 = xRoi + abs(roznicax2);
				yRoi1 = yRoi + abs(roznicay2);

			}

			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> SOUTH - EAST << ";
			direction = 1;
			cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
			cout << "xRoi1 " << xRoi1 << " \t yRoi1 " << yRoi1 << endl;

			line(pers, punkt, Point(punkt.x + 40, punkt.y = 40), Scalar(0, 0, 255), 3, 2);
			punkt = Point(punkt.x + 40, punkt.y + 40);

			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRAŁ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRAŁ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}


		}





		x = x1;
		y = y1;

		x1 = 0;
		y1 = 0;

		xRoi = xRoi1;
		yRoi = yRoi1;

		xRoi1 = 0;
		yRoi1 = 0;

		cout << " PO FORZE " << endl;
		cout << "xRoi " << xRoi << " \t yRoi " << yRoi << endl;
		cout << "xRoi1 " << xRoi1 << " \t yRoi1 " << yRoi1 << endl;


	}





	imshow(destName, pers);
	imwrite("plansza.jpg", pers);

	return 0;
}

int main(int argc, char** argv) {

	Mat zdjecie;
	Mat convert;
	Mat odczyt;
	Mat pers;



	VideoCapture cap(0); // open the video camera no. 0

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);

	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

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
			imwrite("zdjecie.jpg", zdjecie);


			Mat zdj = imread("zdjecie.jpg", 0);


			imshow("zdj",zdj);
			pers = perspective(zdj);
			imshow("ssss", pers);
			DetectLines(pers, "test", "test");
			waitKey(0);

		}


	}
	waitKey(0);

}
