#include<opencv.hpp>
#include<iostream>
#include"resource.h"
using namespace cv;
using namespace std;

/*
date:2019/7/19
author:huanglei
function:图像轮廓与图像分割修复
*/
class imageCountAndInpaint {
public:
	int helloworld();

	//寻找图像轮廓
	int findContoursTest();

	//读取灰度图片测试
	int imreadImage();

	//寻找绘制物体凸包
	int convexHullTest();

	//使用多边形包围轮廓
	int findContoursEdge();

	//分水岭算法
	void watershedImageTest();

	//图像修补
	void imageInpaint();
};
