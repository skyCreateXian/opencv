#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class imageDue {
public:
	//Canny��Ե��⼰��߼�Ӧ��
	int edgeCheck();

	//sobel���ݶȷ����ϵı�Ե���
	int sobelEdge();

	//����任
	int hougLines();

	//ͼ����ӳ��
	int remapImage();

	//ֱ�����⻯
	int equalHist();

	//�ۼƸ��ʻ���任
	int hougLinesP();
};
