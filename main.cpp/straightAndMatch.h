#include<opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std; 

/*
date:2019/7/23
author:huanglei
function:ֱ����ƥ��
*/

class straightAndMatch {
public:
	//����HSֱ��ͼ
	void paintHSMap();

	//����һάֱ��ͼ
	void paintOneMap();

	//����RGB��ɫֱ��ͼ
	void paintThreeMap();

	//ֱ��ͼ�Ա�
	void compareMap();

	//����ӳ��
	void backProject();

	//ģ��ƥ��
	void matchTemplate();
};