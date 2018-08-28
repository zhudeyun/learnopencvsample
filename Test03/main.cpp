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
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
Mat srcImage, grayImage, dstImage;

void thresh_callback(int, void*);

int main()
{
	namedWindow(window_name, WINDOW_AUTOSIZE);
	//加载分类器	
	face_cascade.load("D:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml");
	eyes_cascade.load("D:\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml");
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
	//定义七种颜色用于标注人脸
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
	vector<Rect> faces;
	face_cascade.detectMultiScale(grayImage, faces, scaleFactor, minNeighbors, 0);
	printf("检测到人脸个数:%d", faces.size());
	//标记人脸
	for (int i = 0; i < faces.size(); i++)
	{
		//Point  center;
		//int radius;
		//center.x = cvRound((faces[i].x + faces[i].width * 0.5));
		//center.y = cvRound((faces[i].y + faces[i].height * 0.5));

		//radius = cvRound((faces[i].width + faces[i].height) * 0.25);
		//circle(dstImage, center, radius, colors[i % 7], 2);	//draw circle

		rectangle(dstImage, faces[i], colors[i % 7], 2, 8, 0);	//draw rect

		Mat faceROI = grayImage(faces[i]);	//detect face roi

		vector<Rect> eyes;
		//-- In each face, detect eyes  
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 1, CV_HAAR_DO_ROUGH_SEARCH, Size(3, 3));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			Rect rect(faces[i].x + eyes[j].x, faces[i].y + eyes[j].y, eyes[j].width, eyes[j].height);

			Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);  
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);  
			circle(dstImage, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);  
			
			//rectangle(dstImage, rect, colors[i % 7], 2, 8, 0);
		}
	}
	imshow("人脸识别", dstImage);
	
}