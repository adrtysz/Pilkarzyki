#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;


bool wygranaGraczaPierwszego(Point punkt);
bool wygranaGraczaDrugiego(Point punkt);
void PrintWinner(String name);