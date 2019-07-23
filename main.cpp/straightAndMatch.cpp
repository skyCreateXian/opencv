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
	//MatND���ڴ洢ֱ��ͼ��һ�����ݽṹ
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
				Point(hue * scale, saturation * scale),//�����϶Խǵ�
				Point((hue + 1) * scale - 1,//�����¶Խǵ�
				(saturation + 1) * scale - 1),
				Scalar::all(intensity),//������ɫ
				FILLED//�ߵĺ��
			);
		}
	}
	imshow("ԭͼ", src);
	imshow("H-Sֱ��ͼ", histImg);
	waitKey();
}

void straightAndMatch::paintOneMap()
{
	Mat src = imread("1.jpg");
	imshow("ԭͼ", src);

	MatND dstHist;
	int dims = 1;
	float hranges[] = { 0,255 };
	const float *ranges[] = { hranges };//const����ֻ����const���Ͳ�������������Ϊֻ��
	int size = 256;
	int channels = 0;

	//����ͼ��ֱ��ͼ
	calcHist(&src,//��������
		1,//�����������
		&channels,//��Ҫͳ�Ƶ�ͨ������
		Mat(),//����
		dstHist,//�������
		dims,//ֱ��ͼά��
		&size,//���ÿ��ά�ȵ�ֱ��ͼ�ߴ������
		ranges);//ÿ��ά��ȡֵ��Χ
	int scale = 1;
	Mat dstImg(size * scale, size, CV_8U, Scalar(0));//����256*256�ĻҶ�ͼ��

	double maxValue = 0;
	double minValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);//����������������ȫ����Сֵ�����ֵ����maxValue
	
	//����ֱ��ͼ
	int hpt = saturate_cast<int>(0.9 * size);//ȡ��==cvRound
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);//��������ֵ
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);//����ͬ����С��ʹ�������ֵΪ1
		rectangle(dstImg, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realValue), Scalar(255));
	}
	imshow("һάֱ��ͼ", dstImg);
	waitKey(0);

}

void straightAndMatch::paintThreeMap()
{
	Mat src;
	src = imread("1.jpg");
	imshow("ԭͼ", src);

	//����
	int bins = 256;
	int hist_size[] = { bins };
	float range[] = { 0,256 };
	const float* ranges[] = { range };
	MatND redHist, grayHist, blueHist;

	//ֱ��ͼ�ļ��� ��ɫ
	int channels_r[] = { 0 };
	calcHist(&src, 1, channels_r, Mat(), redHist, 1, hist_size, ranges, true, false);
	
	int channels_g[] = { 1 };
	calcHist(&src, 1, channels_g, Mat(), grayHist, 1, hist_size, ranges, true, false);

	int channels_b[] = { 2 };
	calcHist(&src, 1, channels_b, Mat(), blueHist, 1, hist_size, ranges, true, false);
	//
	double maxValue_red, maxValue_green, maxValue_blue;
	minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
	minMaxLoc(grayHist, 0, &maxValue_green, 0, 0);
	minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
	int scale = 1;
	int histHeight = 256;
	Mat histImg = Mat::zeros(histHeight, bins * 3, CV_8UC3);

	//����
	for (int i = 0; i < bins; i++)
	{
		float binValue_red = redHist.at<float>(i);
		float binValue_green = grayHist.at<float>(i);
		float binValue_blue = blueHist.at<float>(i);
		int intensity_red = cvRound(binValue_red * histHeight / maxValue_red);
		int intensity_green = cvRound(binValue_green * histHeight / maxValue_green);
		int intensity_blue = cvRound(binValue_blue * histHeight / maxValue_blue);

		rectangle(histImg, Point(i * scale, histHeight - 1), Point((i + 1) * scale - 1, histHeight - intensity_red),Scalar(255,0,0));
		rectangle(histImg, Point((i + bins) * scale, histHeight - 1), Point((i + bins + 1) * scale - 1, histHeight - intensity_green), Scalar(0, 255, 0));
		rectangle(histImg, Point((i + 2 * bins) * scale, histHeight - 1), Point((i + 2 * bins + 1) * scale - 1, histHeight - intensity_blue), Scalar(0, 0, 255));
	}

	//�ڴ�������ʾ�����ƺõ�ֱ��ͼ
	imshow("ͼ���е�RGBzֱ��ͼ", histImg);
	waitKey(0);
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
