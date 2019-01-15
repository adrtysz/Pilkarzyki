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
int xRoi = 100; // pierwsze ROI
int yRoi = 180;

int x = 160; //punkt pocz¹tkowy
int y = 240;

int step = 40;
int xRange = 10;
int maxYRange = step + xRange;
int minYRange = step - xRange;
int direction;
int moveCounter=0;

Point punkt = Point(160, 240);

Scalar SetColor(int moveCounter) {

	if (moveCounter % 2 == 0) {
		return Scalar(0, 0, 255); //czerwony
	}
	else {
		return Scalar(125, 223, 91); //zielony
	}
}

void PrintDirection(int direction) {
	switch (direction){
	case 0:
		cout << ">>KIERUNEK RUCHU - PÓ£NOC<<" << endl;
		break;
	case 1:
		cout << ">>KIERUNEK RUCHU - PO£UDNIE<<" <<endl;
		break;
	case 2:
		cout << ">>KIERUNEK RUCHU - WSCHÓD<<" << endl;
		break;
	case 3:
		cout << ">>KIERUNEK RUCHU - ZACHÓD<<" << endl;
		break;
	case 4:
		cout << ">>KIERUNEK RUCHU - PÓ£NOCNY-WSCHÓD<<" << endl;
		break;
	case 5:
		cout << ">>KIERUNEK RUCHU - PÓ£NOCNY-ZACHÓD<<" << endl;
		break;
	case 6:
		cout << ">>KIERUNEK RUCHU - PO£ÓDNIOWY-ZACHÓD<<" << endl;
		break;
	case 7: 
		cout << ">>KIERUNEK RUCHU - PO£ÓDNIOWY-WSCHÓD<<" << endl;
		break;
	}
}

void PrintCurrentPosition(Point punkt){
	cout << "WSPÓ£RZÊDNE OBECNEJ POZYCJI : \t X: " << punkt.x << " \t Y:" << punkt.y << endl;
	}


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


		if ((((roznicay1 > minYRange) && (roznicay1 < maxYRange))) && ((roznicax1 < xRange) && (roznicax1 > -xRange)) || (((roznicay2 > minYRange) && (roznicay2 < maxYRange))) && ((roznicax2 < xRange) && (roznicax2 > -xRange))) {
			
				line(pers, Point(punkt.x, punkt.y), Point(punkt.x, punkt.y - step), SetColor(moveCounter), 3, 2); //czerwony
		
			moveCounter++;

			direction = 0;
			PrintDirection(direction);
			xRoi = xRoi;
			yRoi = yRoi - step;
			punkt = Point(punkt.x, punkt.y - step);
			PrintCurrentPosition(punkt);
		
			x = punkt.x;
			y = punkt.y;
		}

		else if ((((roznicay1 > -maxYRange) && (roznicay1 < -minYRange))) && ((roznicax1 < xRange) && (roznicax1 > -xRange)) || (((roznicay2 > -maxYRange) && (roznicay2 < -minYRange))) && ((roznicax2 < xRange) && (roznicax2 > -xRange))) {


			line(pers, Point(punkt.x, punkt.y), Point(punkt.x, punkt.y + step), SetColor(moveCounter), 3, 2); //zielony
			
			moveCounter++;

			direction = 1;
			PrintDirection(direction);
			xRoi = xRoi;
			yRoi = yRoi + step;
			punkt = Point(punkt.x, punkt.y + step);
			PrintCurrentPosition(punkt);
			x = punkt.x;
			y = punkt.y;

		}

		else if ((((roznicay1 > -xRange) && (roznicay1 < xRange))) && ((roznicax1 < -minYRange) && (roznicax1 > -maxYRange)) || (((roznicay2 > -xRange) && (roznicay2 < xRange))) && ((roznicax2 < -minYRange) && (roznicax2 > -maxYRange))) {

				line(pers, Point(punkt.x, punkt.y), Point(punkt.x+step, punkt.y), SetColor(moveCounter), 3, 2); //czerwony
			

			moveCounter++;
			direction = 2;
			PrintDirection(direction);
			xRoi = xRoi + step;
			yRoi = yRoi;
			punkt = Point(punkt.x + step, punkt.y);
			PrintCurrentPosition(punkt); 
	

			x = punkt.x;
			y = punkt.y;
		}

		else if ((((roznicay1 > -xRange) && (roznicay1 < xRange))) && ((roznicax1 < maxYRange) && (roznicax1 > minYRange)) || (((roznicay2 > -xRange) && (roznicay2 < xRange))) && ((roznicax2 < maxYRange) && (roznicax2 > minYRange))) {


				line(pers, Point(punkt.x, punkt.y), Point(punkt.x-step, punkt.y), SetColor(moveCounter), 3, 2); //zielony
			

			moveCounter++;

			direction = 3;
			PrintDirection(direction);
			xRoi = xRoi - step;
			yRoi = yRoi;
			punkt = Point(punkt.x - step, punkt.y);
			PrintCurrentPosition(punkt);

			x = punkt.x;
			y = punkt.y;

		}


		else if ((((roznicay1 > minYRange) && (roznicay1 < maxYRange))) && ((roznicax1 < -minYRange) && (roznicax1 > -maxYRange)) || (((roznicay2 > minYRange) && (roznicay2 < maxYRange))) && ((roznicax2 < -minYRange) && (roznicax2 > -maxYRange))) {
			
				line(pers, Point(punkt.x, punkt.y), Point(punkt.x+step, punkt.y - step), SetColor(moveCounter), 3, 2); //zielony
			

			moveCounter++;

			direction = 4;
			PrintDirection(direction);
			xRoi = xRoi + step;
			yRoi = yRoi - step;
			punkt = Point(punkt.x + step, punkt.y - step);
			PrintCurrentPosition(punkt);

			x = punkt.x;
			y = punkt.y;

		}




		else if ((((roznicay1 > minYRange) && (roznicay1 < maxYRange))) && ((roznicax1 < maxYRange) && (roznicax1 > minYRange)) || (((roznicay2 > minYRange) && (roznicay2 < maxYRange))) && ((roznicax2 < maxYRange) && (roznicax2 > minYRange))) {

			line(pers, Point(punkt.x, punkt.y), Point(punkt.x-step, punkt.y - step), SetColor(moveCounter), 3, 2); //zielony
			

			moveCounter++;

			direction = 5;
			PrintDirection(direction);
			xRoi = xRoi - step;
			yRoi = yRoi - step;
			punkt = Point(punkt.x - step, punkt.y - step);
			PrintCurrentPosition(punkt);


			x = punkt.x;
			y = punkt.y;

		}

		else if ((((roznicay1 > -maxYRange) && (roznicay1 < -minYRange))) && ((roznicax1 < maxYRange) && (roznicax1 > minYRange)) || (((roznicay2 > -maxYRange) && (roznicay2 < -minYRange))) && ((roznicax2 < maxYRange) && (roznicax2 > minYRange))) {


				line(pers, Point(punkt.x, punkt.y), Point(punkt.x-step, punkt.y + step), SetColor(moveCounter), 3, 2); //zielony
			

			moveCounter++;

			direction = 6;
			PrintDirection(direction);
			xRoi = xRoi - step;
			yRoi = yRoi + step;
			punkt = Point(punkt.x - step, punkt.y + step);
			PrintCurrentPosition(punkt);
	

			x = punkt.x;
			y = punkt.y;


		}

		else if ((((roznicay1 > -maxYRange) && (roznicay1 < -minYRange))) && ((roznicax1 < -minYRange) && (roznicax1 > -maxYRange)) || (((roznicay2 > -maxYRange) && (roznicay2 < -minYRange))) && ((roznicax2 < -minYRange) && (roznicax2 > -maxYRange))) {

				line(pers, Point(punkt.x, punkt.y), Point(punkt.x+step, punkt.y + step), SetColor(moveCounter), 3, 2); //zielony
			

			moveCounter++;

			direction = 7;
			PrintDirection(direction);
			xRoi = xRoi + step;
			yRoi = yRoi + step;
			punkt = Point(punkt.x + step, punkt.y + step);
			PrintCurrentPosition(punkt);

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
