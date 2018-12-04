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
	Mat zapisz, pers;
	int direction;
	zapisz = imread("ruch0.jpg", 0);
	pers = perspective(zapisz);


	Canny(src, dst, 50, 200, 3);
	cvtColor(dst, cdst, COLOR_GRAY2BGR);


	vector<Vec4i> lines;

	HoughLinesP(dst, lines, 1, CV_PI / 180, 20, 10, 5);

	int x = 160; //punkt pocz¹tkowy
	int y = 240; 

	int x1 = 0; //zmienne dla kolejnych punktów
	int y1 = 0;

	int xRoi;
	int yRoi; //punkty dla ROI

	for (size_t i = 0; i < 1; i++) {
		Vec4i l = lines[i];
		line(pers, Point(l[0]+ xRoi ,l[1] + yRoi), Point(l[2] + xRoi, l[3] + yRoi), Scalar(0, 0, 255), 3, 2);
						//  x1           y1               x2              y2


		cout << "Roznica x2 : " << x - (l[2] + 110) << " \t Roznica x1 : " << x - (l[0] + 110) << endl;
		cout << "Roznica y2 : " << y - (l[3] + 190) << " \t Roznica y1 : " << y - (l[1] + 190) << endl;

		int roznicax1 = x - (l[0]);
		int roznicax2 = x - (l[2]);
		int roznicay1 = y - (l[1]);
		int roznicay2 = y - (l[3]);



		if ((((roznicay1 > 20) && (roznicay1 < 50))) && ((roznicax1 < 10) && (roznicax1 > -10)) || (((roznicay2 > 20) && (roznicay2 < 50))) && ((roznicax2 < 10) && (roznicax2 > -10))) {

			if ((roznicay1 > 20) && (roznicay1 < 50)) {
				y1 = y - roznicay1;
				x1 = x + roznicax1;
			}
			else if ((roznicay2 > 20) && (roznicay2 < 50)) {
				y1 = y - roznicay2;
				x1 = x + roznicax2;
			}

			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> NORTH << ";
			direction = 4;

			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRA£ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRA£ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}






		else if ((((roznicay1 > -50) && (roznicay1 < -20))) && ((roznicax1 < 10) && (roznicax1 > -10)) || (((roznicay2 > -50) && (roznicay2 < -20))) && ((roznicax2 < 10) && (roznicax2 > -10))) {

			if ((roznicay1 > -50) && (roznicay1 < -20)) {
				y1 = y + abs(roznicay1);
				x1 = x + abs(roznicax1);
			}
			else if ((roznicay2 > -50) && (roznicay2 < -20)) {
				y1 = y + abs(roznicay2);
				x1 = x + abs(roznicax2);
			}
			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> SOUTH << ";
			direction = 0;


			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRA£ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRA£ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}





		else if ((((roznicay1 > -10) && (roznicay1 < 10))) && ((roznicax1 < -20) && (roznicax1 > -50)) || (((roznicay2 > -10) && (roznicay2 < 10))) && ((roznicax2 < -20) && (roznicax2 > -50))) {
			
			if ((roznicax1 < -20) && (roznicax1 > -50)) {

				x1 = x + abs(roznicax1);
				y1 = y + abs(roznicay1);

			}

			else if ((roznicax2 < -20) && (roznicax2 > -50)) {
				x1 = x + abs(roznicax2);
				y1 = y + abs(roznicay2);
			}

			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> EAST << ";
			direction = 2;

			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRA£ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRA£ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}





		else if ((((roznicay1 > -10) && (roznicay1 < 10))) && ((roznicax1 < 50) && (roznicax1 > 20)) || (((roznicay2 > -10) && (roznicay2 < 10))) && ((roznicax2 < 50) && (roznicax2 > 20))) {
			
			if ((roznicax1 < 50) && (roznicax1 > 20)) {

				x1 = x - abs(roznicax1);
				y1 = y + abs(roznicay1);

			}

			else if ((roznicax2 < 50) && (roznicax2 > 20)) {
				x1 = x - abs(roznicax2);
				y1 = y + abs(roznicay2);
			}

			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> WEST << ";
			direction = 6;

			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRA£ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRA£ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}





		else if ((((roznicay1 > 20) && (roznicay1 < 50))) && ((roznicax1 < -20) && (roznicax1 > -50)) || (((roznicay2 > 20) && (roznicay2 < 50))) && ((roznicax2 < -20) && (roznicax2 > -50))) {
			
			if ((roznicay1 > 20) && (roznicay1 < 50) && (roznicax1 < -20) && (roznicax1 > -50)) {

				y1 = y - abs(roznicay1);
				x1 = x + abs(roznicax1);

			}
			else if ((roznicay2 > 20) && (roznicay2 < 50) && (roznicax2 < -20) && (roznicax2 > -50)) {

				y1 = y - abs(roznicay2);
				x1 = x + abs(roznicax2);
			}


			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> NORTH - EAST << ";
			direction = 3;

			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRA£ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRA£ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}




		else if ((((roznicay1 > 20) && (roznicay1 < 50))) && ((roznicax1 < 50) && (roznicax1 > 20)) || (((roznicay2 > 20) && (roznicay2 < 50))) && ((roznicax2 < 50) && (roznicax2 > 20))) {
			
			if ((roznicay1 > 20) && (roznicay1 < 50) && (roznicax1 < 50) && (roznicax1 > 20)) {

				y1 = y - abs(roznicay1);
				x1 = x - abs(roznicax1);

			}
			else if ((roznicay2 > 20) && (roznicay2 < 50) && (roznicax2 < 50) && (roznicax2 > 20)) {

				y1 = y - abs(roznicay2);
				x1 = x - abs(roznicax2);
			}



			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> NORTH - WEST << ";
			direction = 5;


			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)){
				cout << "WYGRA£ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRA£ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}




		else if ((((roznicay1 > -50) && (roznicay1 < -20))) && ((roznicax1 < 50) && (roznicax1 > 20)) || (((roznicay2 > -50) && (roznicay2 < -20))) && ((roznicax2 < 50) && (roznicax2 > 20))) {
		

			if ((roznicay1 > -50) && (roznicay1 < -20) && (roznicax1 < 50) && (roznicax1 > 20)) {

					y1 = y + abs(roznicay1);
					x1 = x - abs(roznicax1);

				}

			else if ((roznicay2 > -50) && (roznicay2 < -20) && (roznicax2 < 50) && (roznicax2 > 20)) {

				y1 = y + abs(roznicay2);
				x1 = x - abs(roznicax2);

			}


		cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> SOUTH - WEST << ";
			direction = 7;


			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRA£ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRA£ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}

		}







		else if ((((roznicay1 > -50) && (roznicay1 < -20))) && ((roznicax1 < -20) && (roznicax1 > -50)) || (((roznicay2 > -50) && (roznicay2 < -20))) && ((roznicax2 < -20) && (roznicax2 > -50))) {
			

				if ((roznicay1 > -50) && (roznicay1 < -20) && (roznicax1 < -20) && (roznicax1 > -50)) {

						y1 = y + abs(roznicay1);
						x1 = x + abs(roznicax1);

					}

				else if ((roznicay2 > -50) && (roznicay2 < -20) && (roznicax2 < -20) && (roznicax2 > -50)) {

					y1 = y + abs(roznicay2);
					x1 = x + abs(roznicax2);

				}
			
			cout << "X : " << x1 << " Y : " << y1 << endl;
			cout << "Kierunek >> SOUTH - EAST << ";
			direction = 1;

			if ((x1 > 150) && (x1 < 170) && (y1 > 30) && (y1 < 50)) {
				cout << "WYGRA£ GRACZ PIERWSZY" << endl;
				direction = 8;
				break;
			}
			else if ((x1 > 150) && (x1 < 170) && (y1 > 420) && (y1 < 460)) {
				cout << "WYGRA£ GRACZ DRUGI" << endl;
				direction = 8;
				break;
			}


		}


		


		x = x1;
		y = y1;

		x1 = 0;
		y1 = 0;


		




	}







	imshow(destName, pers);

	return 0;
}

int main(int argc, char** argv) {

	ruch = imread("pdwsch.jpg", 0);
	Mat wyjscie = perspective(ruch);


	Mat ruch0 = imread("ruch0.jpg",0);
	wyjscie2 = perspective(ruch0);



	Mat roi = wyjscie(Rect(110, 190, 100, 100));
	imshow("ROI", roi);


	DetectLines(roi, " test", "test");
	
	waitKey();





	return 0;

}
