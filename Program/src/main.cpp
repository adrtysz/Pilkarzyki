#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "DetectLine.h"
#include "Winner.h"
#include "Perspective.h"

using namespace cv;
using namespace std;
int planszaruch = 0;
Point point;


int main(int argc, char** argv) {
	Mat zdj_old;
	Mat zdjecie;
	Mat pers_old;
	Mat pers_new;
	Mat pers;
	Mat diff;
	Mat nowa_plansza;
	string player1, player2;
	nowa_plansza = imread("new.jpg", 1);
	imwrite("plansza.jpg", nowa_plansza);

	cout << " GRACZ PIERWSZY, PODAJ SWOJE IMIE " << endl;
	cin >> player1;
	cout << player1 << " WITAJ W GRZE" << endl;

	cout << " GRACZ DRUGI, PODAJ SWOJE IMIE " << endl;
	cin >> player2;
	cout << player2 << " WITAJ W GRZE" << endl;

	cout << "GRĘ ZACZYNA " << player1 << endl;


	VideoCapture cap(0); // open the video camera no. 0
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);

	if (!cap.isOpened()){
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	namedWindow("MyVideo", CV_WINDOW_NORMAL);
	resizeWindow("MyVideo", 768, 432);
	moveWindow("MyVideo", 600, 0);

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
		}else if (waitKey(30) == 32) {
			frame.copyTo(zdjecie);
			if (planszaruch > 0){
				zdj_old = imread("zdjecie1.jpg", 0);
				imwrite("zdjecie0.jpg", zdj_old);
			}
			imwrite("zdjecie1.jpg", zdjecie);


			Mat zdj = imread("zdjecie1.jpg", 0);
			if (planszaruch > 0){
				pers_old = perspective(zdj_old);
				pers_new = perspective(zdj);
				absdiff(pers_old, pers_new, diff);
				imshow("xd", diff);
				point = DetectLines(diff, "PLANSZA GRY", "PLANSZA GRY");
				planszaruch++;
				if (wygranaGraczaPierwszego(point) == true) {
					Mat zwyciestwo = imread("wg1.jpg", 1);
					imshow("GRATULACJE", zwyciestwo);
					PrintWinner(player1);
				}
				if (wygranaGraczaDrugiego(point) == true) {
					Mat zwyciestwo = imread("wg2.jpg", 1);
					imshow("GRATULACJE", zwyciestwo);
					PrintWinner(player2);
				}
			}else {
				pers = perspective(zdj);
				DetectLines(pers, "PLANSZA GRY", "PLANSZA GRY");
				planszaruch++;
				}

			}
		}
	waitKey(0);
}