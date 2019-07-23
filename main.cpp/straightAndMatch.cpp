#include"straightAndMatch.h"

void straightAndMatch::paintHSMap()
{
	//����ͼ��ת��ΪHSVģʽ
	Mat src, hsv;
	src = imread("1.jpg");
	cvtColor(src, hsv, COLOR_BGR2HSV);

	//��ɫ��������Ϊ30���ȼ��������ͺͶ�����Ϊ32���ȼ�
	int hueBinNum = 30;//ɫ����ֱ��ͼֱ������
	int sat = 32;
	int hist[] = { hueBinNum,sat };//��hue��sat��������

	//����ɫ���ı仯��ΧΪ0��179
	float hueRanges[] = { 0,180 };
	//���履�Ͷȵı仯��ΧΪ0���ڰ׻ң���255����������ɫ��
	float satRanges[] = { 0,255 };

	const float* ranges[] = { hueRanges,satRanges };
	MatND dstHist;
	//calcHist�����н������0ͨ���͵�һͨ����ֱ��ͼ

	int channels[] = { 0,1 };

	//����calcHist������ֱ��ͼ����
	calcHist(&hsv,//��������
		1,//�������
		channels,//ͨ������
		Mat(),//��ʹ����ģ
		dstHist,//�����Ŀ��ֱ��ͼ
		2,//��Ҫ�����ֱ��ͼ��ά��Ϊ2
		hist,//���ÿ��ά�ȵ�ֱ��ͼ�ߴ������
		ranges,//ÿһά��ȡֵ��Χ����
		true,//ָʾֱ��ͼ�Ƿ���ȵı�ʶ��
		false);//�ۼƱ�ʶ����f��ʾֱ��ͼ��ƥ��׶λᱻ��0
	
	//����ֱ��ͼ��Ҫ����
	double maxValue = 0;//���ֵ
	//���������ҵ�ȫ����Сֵ�����ֵ
	minMaxLoc(dstHist,//��������
		0,//�޷�����Сָ��
		&maxValue,//�������ָ��
		0,//�޷�����Сλ�õ�ָ��
		0);//�޷������λ�õ�ָ��
	//���һ��������ѡ�����������еĿ�ѡ��Ĥ

	int scale = 10;
	//����һ����Ϊ��һ����������Ϊ�ڶ�������������Ϊ�����������Ŀհ�ͼ��
	Mat histImg = Mat::zeros(sat * scale, hueBinNum * 10, CV_8UC3);

	for ( int hue = 0; hue < hueBinNum; hue++)//����ɫ��
	{
		for (int saturation = 0; saturation < sat; saturation++) {//�������Ͷ�
			float binValue = dstHist.at<float>(hue, saturation);//����ͼ������
			int intensity = cvRound(binValue * 255 / maxValue);//ǿ��
			//�����λ��ƺ���
			rectangle(
				histImg,
				Point(hue * scale, saturation * scale),
				Point((hue + 1) * scale - 1,
				(saturation + 1) * scale - 1),
				Scalar::all(intensity),
				FILLED
			);
		}
	}
	imshow("ԭͼ", src);
	imshow("H-Sֱ��ͼ", histImg);
	waitKey();
}

void straightAndMatch::paintOneMap()
{
}

void straightAndMatch::paintThreeMap()
{
}

void straightAndMatch::compareMap()
{
}

void straightAndMatch::backProject()
{
}

void straightAndMatch::matchTemplate()
{
}
