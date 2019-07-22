#include"imageDue.h"
//Canny��Ե��⼰��߼�Ӧ��
int imageDue::edgeCheck() {
	//����ͼ��
	Mat src = imread("1.jpg");
	Mat src1 = src.clone();//��ȫ��������src��������Ϣ������src1��

	imshow("��ԭʼͼ��Canny��Ե���", src);
	//�õ�ͼ��ֱ��canny��Ե����ѱ�opencv3����
	Canny(src, src, 150, 100, 3);
	imshow("��Ч��ͼ��Canny��Ե���", src);

	//Canny�߽ײ���

	Mat dst, edge, gray;
	//������src��С��ȵľ���(��������
	dst.create(src1.size(), src1.type());
	//��ͼ��ת��Ϊ�Ҷ�ͼ��
	cvtColor(src1, gray, COLOR_BGR2GRAY);

	imshow("���Ҷ�ͼ��", gray);

	//ʹ��3x3�ں˽���
	blur(gray, edge, Size(3, 3));
	imshow("���Ҷ�ͼ�����", edge);

	Canny(edge, edge, 3, 9, 3);
	imshow("���Ҷ�ͼ���Ե��⡿", edge);

	src1.copyTo(dst, edge);
	imshow("����ɫ��Ե���Ч����", dst);
	waitKey(0);
	return 0;
}

int imageDue::sobelEdge() {

	//�����ݶȷ���Ϊx��y�ľ���
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	//����ͼ��
	Mat src = imread("1.jpg");
	imshow("��ԭͼ��", src);

	Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("��x����Sobel��", abs_grad_x);

	Sobel(src, grad_y, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);//ͼ����ǿ
	imshow("��y����Sobel��", abs_grad_y);

	//�ϲ��ݶ�
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("���ϲ��ݶ�Ч����", dst);

	waitKey(0);
	return 0;
}

//����任(�˺������������⣩
int imageDue::hougLines() {
	Mat src = imread("1.jpg");
	Mat mid, dis;
	//������Ե���ͻҶȴ�����ܵõ�8λ��ͨ��������ͼ��
	Canny(src, mid, 50, 200, 3);
	cvtColor(mid, dis, COLOR_GRAY2BGR);
	vector<Vec2f> lines;
	HoughLines(mid, lines, 1, CV_PI / 180, 150, 0, 0);
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * b);
		pt1.y = cvRound(y0 + 1000 * a);
		pt2.x = cvRound(x0 + 1000 * b);
		pt2.y = cvRound(y0 + 1000 * a);
		line(dis, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);

	}
	imshow("ԭʼͼ", src);

	imshow("��Ե���ͼ", mid);

	imshow("����任ͼ", dis);

	waitKey(0);
	return 0;
}
//
int imageDue::hougLinesP() {

	Mat src = imread("1.jpg");
	Mat mid, dis;
	//������Ե���ͻҶȴ�����ܵõ�8λ��ͨ��������ͼ��
	Canny(src, mid, 50, 200, 3);
	cvtColor(mid, dis, COLOR_GRAY2BGR);
	vector<Vec4i> lines;
	HoughLinesP(mid, lines, 1, CV_PI / 180, 80, 50, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];

		line(dis, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255));

	}
	imshow("ԭʼͼ", src);

	imshow("��Ե���ͼ", mid);

	imshow("����任ͼ", dis);

	waitKey(0);
	return 0;
}
//ͼ����ӳ��
int imageDue::remapImage() {
	Mat src, dst;
	Mat map_x, map_y;
	src = imread("1.jpg", 1);
	dst = imread("1.jpg");
	imshow("ԭʼͼ", src);
	imshow("ԭʼͼ", dst);
	dst.create(src.size(), src.type());
	map_x.create(src.size(), CV_32FC1);
	map_y.create(src.size(), CV_32FC1);
	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++) {
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(src.rows - j);
		}
	}
	remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	imshow("��ӳ��", dst);
	waitKey(0);
	return 0;
}

int imageDue::equalHist() {
	Mat src, dst;
	src = imread("1.jpg", 1);
	cvtColor(src, src, COLOR_BGR2GRAY);
	imshow("�Ҷ�ͼ��", src);

	equalizeHist(src, dst);
	imshow("ֱ�����⻯", dst);
	waitKey(0);
	return 0;
}