#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;


bool wygranaGraczaPierwszego(Point punkt) {
	if (punkt.x == 160 && punkt.y == 40) return true;
}
bool wygranaGraczaDrugiego(Point punkt) {
	if (punkt.x == 160 && punkt.y == 440) return true;
}
void PrintWinner(String name) {
	cout << " KONIEC GRY " << endl;
	cout << " ZWYCIEZCA TO : " << name << endl;
}
