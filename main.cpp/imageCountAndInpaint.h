#include<opencv.hpp>
#include<iostream>
#include"resource.h"
using namespace cv;
using namespace std;

/*
date:2019/7/19
author:huanglei
function:ͼ��������ͼ��ָ��޸�
*/
class imageCountAndInpaint {
public:
	int helloworld();

	//Ѱ��ͼ������
	int findContoursTest();

	//��ȡ�Ҷ�ͼƬ����
	int imreadImage();

	//Ѱ�һ�������͹��
	int convexHullTest();

	//ʹ�ö���ΰ�Χ����
	int findContoursEdge();

	//��ˮ���㷨
	void watershedImageTest();

	//ͼ���޲�
	void imageInpaint();
};
