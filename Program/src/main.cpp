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

	// NALE¯Y DODAÆ 8 KIERUNEK KTÓRYM HEST BRAMKA, CZYLI JEŒLI WSPÓLRZÊDNE KTOREGOS Z PUNKTOW ZNALEZIONEJ LINII BÊD¥ RÓWNE 
	// X = 160, A Y = 40 LUB Y = 440, OCZYWIŒCIE +- JAKIŒ B£¥D 
	// DODATKOWO ROZNICA LICZONA JEST "NA SZTYWNO " WZGLÊDEM PUNKTU STARTOWEGO CZYLI (160,240) A MUSI MYÆ TO ROBIONE DYNAMICZNIE, CZYLI
	// PUNKT KONCOWY ZNALEZIONEJ LINII JEST KOLEJNYM PUNKTEM STARTOWYM + ROWNIEZ TRZEBA ZMIENIAÆ DYNAMICZNIE OBSZAR POSZUKIWANIA LINII
	// CZYLI ROI (JEST W MAINIE) TAK ZEBY PUNKT KONCOWY LINII KTORA ZNALEZLISMY BYL W SRODKU OBSZARU ZAINTERESOWANIA 


	Canny(src, dst, 50, 200, 3);
	cvtColor(dst, cdst, COLOR_GRAY2BGR);


	vector<Vec4i> lines;

	HoughLinesP(dst, lines, 1, CV_PI / 180, 20, 10, 5);

	for (size_t i = 0; i < 1; i++){
		Vec4i l = lines[i];
		line(pers, Point(l[0] + 110, l[1] + 180), Point(l[2] + 110, l[3] + 180), Scalar(0, 0, 255), 3, 2);
		                 //  x1         y1               x2              y2

		//punkt startowy (160,240)


		cout << "Roznica x2 : " << 160 - (l[2] + 110) << " \t Roznica x1 : " << 160 - (l[0] + 110) << endl;
		cout << "Roznica y2 : " << 240 - (l[3] + 190) << " \t Roznica y1 : " << 240 - (l[1] + 190) << endl;

		int roznicax1 = 160 - (l[0] + 110);
		int roznicax2 = 160 - (l[2] + 110);
		int roznicay1 = 240 - (l[1] + 190);
		int roznicay2 = 240 - (l[3] + 190);


		if ((((roznicay1 > 20) && (roznicay1 < 50))) && ((roznicax1 < 10) && (roznicax1 > -10)) || (((roznicay2 > 20) && (roznicay2 < 50))) && ((roznicax2 < 10) && (roznicax2 > -10))) {

			cout << "Kierunek >> NORTH << ";
			direction = 4;
		}



		else if ((((roznicay1 > -50) && (roznicay1 < -20))) && ((roznicax1 < 10) && (roznicax1 > -10)) || (((roznicay2 > -50) && (roznicay2 < -20))) && ((roznicax2 < 10) && (roznicax2 > -10))) {

			cout << "Kierunek >> SOUTH << ";
			direction = 0;
		}


		else if ((((roznicay1 > -10) && (roznicay1 < 10))) && ((roznicax1 < -20) && (roznicax1 > -50)) || (((roznicay2 > -10) && (roznicay2 < 10))) && ((roznicax2 < -20) && (roznicax2 > -50))) {

			cout << "Kierunek >> EAST << ";
			direction = 2;
		}


		else if ((((roznicay1 > -10) && (roznicay1 < 10))) && ((roznicax1 < 50) && (roznicax1 > 20)) || (((roznicay2 > -10) && (roznicay2 < 10))) && ((roznicax2 < 50) && (roznicax2 > 20))) {

			cout << "Kierunek >> WEST << ";
			direction = 6;
		}


		else if ((((roznicay1 > 20) && (roznicay1 < 50))) && ((roznicax1 < -20) && (roznicax1 > -50)) || (((roznicay2 > 20) && (roznicay2 < 50))) && ((roznicax2 < -20) && (roznicax2 > -50))) {

			cout << "Kierunek >> NORTH - EAST << ";
			direction = 3;
		}


		else if ((((roznicay1 > 20) && (roznicay1 < 50))) && ((roznicax1 < 50) && (roznicax1 > 20)) || (((roznicay2 > 20) && (roznicay2 < 50))) && ((roznicax2 < 50) && (roznicax2 > 20))) {

			cout << "Kierunek >> NORTH - WEST << ";
			direction = 5;
		}


		else if ((((roznicay1 > -50) && (roznicay1 < -20))) && ((roznicax1 < 50) && (roznicax1 > 20)) || (((roznicay2 > -50) && (roznicay2 < -20))) && ((roznicax2 < 50) && (roznicax2 > 20))) {

			cout << "Kierunek >> SOUTH - WEST << ";
			direction = 7;
		}


		else if ((((roznicay1 > -50) && (roznicay1 < -20))) && ((roznicax1 < -20) && (roznicax1 > -50)) || (((roznicay2 > -50) && (roznicay2 < -20))) && ((roznicax2 < -20) && (roznicax2 > -50))) {

			cout << "Kierunek >> SOUTH - EAST << ";
			direction = 1;
		}



		

	}

	





	imshow(destName, pers);

	return 0;
}

int main(int argc, char** argv) {

	ruch = imread("pdwsch.jpg", 0);
	wyjscie = perspective(ruch);




	Mat roi = wyjscie(Rect(110, 190, 100, 100));
	imshow("ROI", roi);


	//Mat test;
	//absdiff(wyjscie3, wyjscie2, test);

	DetectLines(roi, "line src", "line dest");
	//imwrite("diff.jpg", test);
	waitKey();





	return 0;

}
