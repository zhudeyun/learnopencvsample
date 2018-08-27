#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>
#include <cstdio>
using namespace cv;
using namespace std;
double scaleFactor = 1.1;
int minNeighbors = 3;
const char* window_name = "window";
CascadeClassifier cascade;
Mat srcImage, grayImage, dstImage;

void thresh_callback(int, void*);

int main()
{
	namedWindow(window_name, WINDOW_AUTOSIZE);
	//加载分类器	
	cascade.load("D:\\H149042\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml");
	
	//读取图片
	srcImage = imread("hero.jpg");
	
	imshow(window_name, srcImage);
	//转灰度图
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	
	//创建轨迹条
	createTrackbar("scaleFactor:", window_name, &minNeighbors, 20, thresh_callback);
	thresh_callback(0, 0);
	waitKey(0);
	return 0;
}

void thresh_callback(int, void*)
{
	//定义其中颜色用于标注人脸
	Scalar colors[] =
	{
		// 红橙黄绿青蓝紫
		CV_RGB(255, 0, 0),
		CV_RGB(255, 97, 0),
		CV_RGB(255, 255, 0),
		CV_RGB(0, 255, 0),
		CV_RGB(0, 255, 255),
		CV_RGB(0, 0, 255),
		CV_RGB(160, 32, 240)
	};
	dstImage = srcImage.clone();
	//检测人脸
	vector<Rect> rect;
	cascade.detectMultiScale(grayImage, rect, scaleFactor, minNeighbors, 0);
	printf("检测到人脸个数:%d", rect.size());
	//标记人脸
	for (int i = 0; i < rect.size(); i++)
	{
		Point  center;
		int radius;
		center.x = cvRound((rect[i].x + rect[i].width * 0.5));
		center.y = cvRound((rect[i].y + rect[i].height * 0.5));

		radius = cvRound((rect[i].width + rect[i].height) * 0.25);
		circle(dstImage, center, radius, colors[i % 7], 2);
	}
	imshow("人脸识别", dstImage);
	
}