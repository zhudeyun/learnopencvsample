#include <stdio.h>
#include "opencv2/opencv.hpp"
using namespace cv;

void main()
{
	Mat mat = imread("1.jpg");
	imshow("image", mat);
	waitKey(0);
	return;
}