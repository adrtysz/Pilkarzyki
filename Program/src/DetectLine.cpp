#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "GetRoi.h"
#include "Winner.h"

using namespace cv;
using namespace std;

int roiCenter = 60;
int xRoi = 100;
int yRoi = 180;

int x = 160; //punkt pocz¹tkowy
int y = 240;


Point punkt = Point(160, 240);

int DetectLines(Mat src, const char* sourceName, const char* destName) {

	Mat dst;
	Mat pers = imread("plansza.jpg", 1);
	
	Mat roi = getPaddedROI(src, xRoi, yRoi, 120, 120,Scalar(0,0,0));
	imshow("roi", roi);

	Canny(roi, dst, 100, 150, 3);
	imshow("canny", dst);
	vector<Vec4i> lines;

	HoughLinesP(dst, lines, 1, CV_PI / 180, 10, 10, 15);

	for (size_t i = 0; i < 1; i++) {

		Vec4i l = lines[i];

		int roznicax1 = roiCenter - (l[0]);
		int roznicax2 = roiCenter - (l[2]);
		int roznicay1 = roiCenter - (l[1]);
		int roznicay2 = roiCenter - (l[3]);


		if ((((roznicay1 > 30) && (roznicay1 < 50))) && ((roznicax1 < 10) && (roznicax1 > -10)) || (((roznicay2 > 30) && (roznicay2 < 50))) && ((roznicax2 < 10) && (roznicax2 > -10))) {
			line(pers, Point(punkt.x, punkt.y), Point(punkt.x, punkt.y - 40), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> NORTH << ";
			xRoi = xRoi;
			yRoi = yRoi - 40;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x, punkt.y - 40);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl << endl;
		
			x = punkt.x;
			y = punkt.y;
		}

		else if ((((roznicay1 > -50) && (roznicay1 < -30))) && ((roznicax1 < 10) && (roznicax1 > -10)) || (((roznicay2 > -50) && (roznicay2 < -30))) && ((roznicax2 < 10) && (roznicax2 > -10))) {


			line(pers, punkt, Point(punkt.x, punkt.y + 40), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> SOUTH << ";
			xRoi = xRoi;
			yRoi = yRoi + 40;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x, punkt.y + 40);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl << endl;
			x = punkt.x;
			y = punkt.y;

		}

		else if ((((roznicay1 > -10) && (roznicay1 < 10))) && ((roznicax1 < -30) && (roznicax1 > -50)) || (((roznicay2 > -10) && (roznicay2 < 10))) && ((roznicax2 < -30) && (roznicax2 > -50))) {

			line(pers, punkt, Point(punkt.x + 40, punkt.y), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> EAST<< ";
			xRoi = xRoi + 40;
			yRoi = yRoi;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x + 40, punkt.y);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl<<endl;
	

			x = punkt.x;
			y = punkt.y;
		}





		else if ((((roznicay1 > -10) && (roznicay1 < 10))) && ((roznicax1 < 50) && (roznicax1 > 30)) || (((roznicay2 > -10) && (roznicay2 < 10))) && ((roznicax2 < 50) && (roznicax2 > 30))) {


			line(pers, punkt, Point(punkt.x - 40, punkt.y), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> WEST << ";
			xRoi = xRoi - 40;
			yRoi = yRoi;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x - 40, punkt.y);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl<<endl;
	


			x = punkt.x;
			y = punkt.y;

		}


		else if ((((roznicay1 > 30) && (roznicay1 < 50))) && ((roznicax1 < -30) && (roznicax1 > -50)) || (((roznicay2 > 30) && (roznicay2 < 50))) && ((roznicax2 < -30) && (roznicax2 > -50))) {


			line(pers, punkt, Point(punkt.x + 40, punkt.y - 40), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> NORTH - EAST << ";
			xRoi = xRoi + 40;
			yRoi = yRoi - 40;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x + 40, punkt.y - 40);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl<<endl;

			x = punkt.x;
			y = punkt.y;

		}




		else if ((((roznicay1 > 30) && (roznicay1 < 50))) && ((roznicax1 < 50) && (roznicax1 > 30)) || (((roznicay2 > 30) && (roznicay2 < 50))) && ((roznicax2 < 50) && (roznicax2 > 30))) {


			line(pers, punkt, Point(punkt.x - 40, punkt.y - 40), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> NORTH - WEST << ";
			xRoi = xRoi - 40;
			yRoi = yRoi - 40;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x - 40, punkt.y - 40);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl<<endl;


			x = punkt.x;
			y = punkt.y;

		}

		else if ((((roznicay1 > -50) && (roznicay1 < -30))) && ((roznicax1 < 50) && (roznicax1 > 30)) || (((roznicay2 > -50) && (roznicay2 < -30))) && ((roznicax2 < 50) && (roznicax2 > 30))) {

			line(pers, punkt, Point(punkt.x - 40, punkt.y + 40), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> SOUTH - WEST << ";
			xRoi = xRoi - 40;
			yRoi = yRoi + 40;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x - 40, punkt.y + 40);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl<<endl;
	

			x = punkt.x;
			y = punkt.y;


		}

		else if ((((roznicay1 > -50) && (roznicay1 < -30))) && ((roznicax1 < -30) && (roznicax1 > -50)) || (((roznicay2 > -50) && (roznicay2 < -30))) && ((roznicax2 < -30) && (roznicax2 > -50))) {

			line(pers, punkt, Point(punkt.x + 40, punkt.y + 40), Scalar(0, 0, 255), 3, 2);

			cout << "Kierunek >> SOUTH - EAST<< ";
			xRoi = xRoi + 40;
			yRoi = yRoi + 40;
			cout << "NOWY PUNKT POCZATKOWY : " << endl;
			punkt = Point(punkt.x + 40, punkt.y + 40);
			cout << "X :" << punkt.x << "\t Y : " << punkt.y << endl<<endl;

			x = punkt.x;
			y = punkt.y;

		}


	}
	if (wygranaGraczaPierwszego(punkt) == true) {

		Mat zwyciestwo = imread("wg1.jpg", 1);
		imshow("GRATULACJE", zwyciestwo);
	}
	if (wygranaGraczaDrugiego(punkt) == true) {

		Mat zwyciestwo = imread("wg2.jpg", 1);
		imshow("GRATULACJE", zwyciestwo);
	}

	imshow(destName, pers);
	imwrite("plansza.jpg", pers);

	return 0;
}
