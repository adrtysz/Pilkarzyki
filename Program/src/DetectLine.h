#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Point DetectLines(Mat src, const char* sourceName, const char* destName);
void PrintDirection(int direction);
void PrintCurrentPosition(Point punkt);
Scalar SetColor(int moveCounter);
bool SouthEast(int x1, int y1, int x2, int y2);
bool SouthWest(int x1, int y1, int x2, int y2);
bool NorthEast(int x1, int y1, int x2, int y2);
bool NorthWest(int x1, int y1, int x2, int y2);
bool South(int x1, int y1, int x2, int y2);
bool North(int x1, int y1, int x2, int y2);
bool East(int x1, int y1, int x2, int y2);
bool West(int x1, int y1, int x2, int y2);
