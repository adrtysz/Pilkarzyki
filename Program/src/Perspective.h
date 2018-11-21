

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

void drawLine(Vec2f, Mat, Scalar);
void mergeRelatedLines(vector<Vec2f>, Mat);
int perspective(Mat);