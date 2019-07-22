#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class imageDue {
public:
	//Canny边缘检测及其高级应用
	int edgeCheck();

	//sobel多梯度方向上的边缘检测
	int sobelEdge();

	//霍夫变换
	int hougLines();

	//图像重映射
	int remapImage();

	//直方均衡化
	int equalHist();

	//累计概率霍夫变换
	int hougLinesP();
};
