#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "FindContours.h"
#include "Contours.h"
#include "CameraStart.h"


using namespace cv;
using namespace std;

Mat src1; 
Mat camerainput;

/** @function main */
int main(int argc, char** argv)
{
	/// Load source image and convert it to gray
	//src1 = imread(argv[1], 1);
	char key; 
	//load(src1);
	//loadAndCrop(src1);
	//camera();
	while (true)
	{
		std::cin >> key;
		while(key == 32 || key == ' ');
		{	
			//cout << "test";
			camerainput = camera();
			load(camerainput);
			loadAndCrop(camerainput);
			
		}
		key = 'a';
		
	}
}


