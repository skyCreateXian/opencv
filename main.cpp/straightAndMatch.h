#include<opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std; 

/*
date:2019/7/23
author:huanglei
function:直方与匹配
*/

class straightAndMatch {
public:
	//绘制HS直方图
	void paintHSMap();

	//绘制一维直方图
	void paintOneMap();

	//绘制RGB三色直方图
	void paintThreeMap();

	//直方图对比
	void compareMap();

	//反向映射
	void backProject();

	//模板匹配
	void matchTemplate();
};