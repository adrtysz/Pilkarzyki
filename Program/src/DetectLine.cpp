#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "GetRoi.h"

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

bool North(int x1, int y1, int x2, int y2) {
	if ((((y1 > minYRange) && (y1 < maxYRange))) && ((x1 < xRange) && (x1 > -xRange)) || (((y2 > minYRange) && (y2 < maxYRange))) && ((x2 < xRange) && (x2 > -xRange))) {
		return true;
	}else {
		return false;
	}
}

bool South(int x1, int y1, int x2, int y2) {
	if ((((y1 > -maxYRange) && (y1 < -minYRange))) && ((x1 < xRange) && (x1 > -xRange)) || (((y2 > -maxYRange) && (y2 < -minYRange))) && ((x2 < xRange) && (x2 > -xRange))) {
		return true;
	}else {
		return false;
	}
}

bool East(int x1, int y1, int x2, int y2) {
	if ((((y1 > -xRange) && (y1 < xRange))) && ((x1 < -minYRange) && (x1 > -maxYRange)) || (((y2 > -xRange) && (y2 < xRange))) && ((x2 < -minYRange) && (x2 > -maxYRange))) {
		return true;
	}else {
		return false;
	}
}

bool West(int x1, int y1, int x2, int y2) {
	if ((((y1 > -xRange) && (y1 < xRange))) && ((x1 < maxYRange) && (x1 > minYRange)) || (((y2 > -xRange) && (y2 < xRange))) && ((x2 < maxYRange) && (x2 > minYRange))) {
		return true;
	}else {
		return false;
	}
}

bool NorthEast(int x1, int y1, int x2, int y2) {
	if ((((y1 > minYRange) && (y1 < maxYRange))) && ((x1 < -minYRange) && (x1 > -maxYRange)) || (((y2 > minYRange) && (y2 < maxYRange))) && ((x2 < -minYRange) && (x2 > -maxYRange))) {
		return true;
	}else {
		return false;
	}
}

bool NorthWest(int x1, int y1, int x2, int y2) {
	if ((((y1 > minYRange) && (y1 < maxYRange))) && ((x1 < maxYRange) && (x1 > minYRange)) || (((y2 > minYRange) && (y2 < maxYRange))) && ((x2 < maxYRange) && (x2 > minYRange))) {
		return true;
	}else {
		return false;
	}
}

bool SouthWest(int x1, int y1, int x2, int y2) {
	if ((((y1 > -maxYRange) && (y1 < -minYRange))) && ((x1 < maxYRange) && (x1 > minYRange)) || (((y2 > -maxYRange) && (y2 < -minYRange))) && ((x2 < maxYRange) && (x2 > minYRange))) {
		return true;
	}else {
		return false;
	}
}
bool SouthEast(int x1, int y1, int x2, int y2) {
	if ((((y1 > -maxYRange) && (y1 < -minYRange))) && ((x1 < -minYRange) && (x1 > -maxYRange)) || (((y2 > -maxYRange) && (y2 < -minYRange))) && ((x2 < -minYRange) && (x2 > -maxYRange))) {
		return true;
	}else {
		return false;
	}
}

Scalar SetColor(int moveCounter) {
	if (moveCounter % 2 == 0) {
		return Scalar(0, 0, 255); //czerwony
	}else {
		return Scalar(125, 223, 91); //zielony
	}
}

void PrintDirection(int direction) {
	switch (direction){
	case 0:
		cout << ">>KIERUNEK RUCHU - POLNOC<<" << endl;
		break;
	case 1:
		cout << ">>KIERUNEK RUCHU - POLUDNIE<<" <<endl;
		break;
	case 2:
		cout << ">>KIERUNEK RUCHU - WSCHOD<<" << endl;
		break;
	case 3:
		cout << ">>KIERUNEK RUCHU - ZACHOD<<" << endl;
		break;
	case 4:
		cout << ">>KIERUNEK RUCHU - POLNOCNY-WSCHOD<<" << endl;
		break;
	case 5:
		cout << ">>KIERUNEK RUCHU - POLNOCNY-ZACHOD<<" << endl;
		break;
	case 6:
		cout << ">>KIERUNEK RUCHU - POLODNIOWY-ZACHOD<<" << endl;
		break;
	case 7: 
		cout << ">>KIERUNEK RUCHU - POLODNIOWY-WSCHOD<<" << endl;
		break;
	}
}

void PrintCurrentPosition(Point punkt){
	cout << "WSPÓ£RZÊDNE OBECNEJ POZYCJI : \t X: " << punkt.x << " \t Y:" << punkt.y << endl;
	}

Point DetectLines(Mat src, const char* sourceName, const char* destName) {

	Mat dst;
	Mat pers = imread("plansza.jpg", 1);
	
	Mat roi = getPaddedROI(src, xRoi, yRoi, 120, 120,Scalar(0,0,0));
	imshow("roi", roi);

	Canny(roi, dst, 100, 150, 3);
	imshow("canny", dst);
	vector<Vec4i> lines;

	HoughLinesP(dst, lines, 1, CV_PI / 180, 10, 5, 20);

	for (size_t i = 0; i < 1; i++) {

		Vec4i l = lines[i];

		int roznicax1 = roiCenter - (l[0]);
		int roznicax2 = roiCenter - (l[2]);
		int roznicay1 = roiCenter - (l[1]);
		int roznicay2 = roiCenter - (l[3]);


		if (North(roznicax1,roznicay1,roznicax2,roznicay2)) {	
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
		else if (South(roznicax1,roznicay1,roznicax2,roznicay2)) {
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
		else if(East(roznicax1,roznicay1,roznicax2,roznicay2)) {
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
		else if (West(roznicax1,roznicay1,roznicax2,roznicay2)){
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
		else if (NorthEast(roznicax1,roznicay1,roznicax2,roznicay2)) {
			line(pers, Point(punkt.x, punkt.y), Point(punkt.x+step, punkt.y - step), SetColor(moveCounter), 3, 2);
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
		else if (NorthWest(roznicax1,roznicay1,roznicax2,roznicay2)) {
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
		else if (SouthWest(roznicax1,roznicay1,roznicax2,roznicay2)) {
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
		else if (SouthEast(roznicax1,roznicay1,roznicax2,roznicay2)){
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
	imshow(destName, pers);
	imwrite("plansza.jpg", pers);

	return punkt;
}
