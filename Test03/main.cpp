#include "opencv2/opencv.hpp"
using namespace cv;
int main()
{
	Mat src = imread("lena.jpg");
	imshow("window", src);
	waitKey(0);
	return 0;
}