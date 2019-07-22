#include"imageCountAndInpaint.h"

#define WINDOW_NAME1 "��ԭͼ��"
#define WINDOW_NAME2 "��Ч��ͼ��"


Mat g_src;
Mat g_gray;
Mat g_mask;
int g_maxThresh = 255;
int g_nTgresh = 50;
RNG g_rng(12345);
Mat g_threshold_out;
Mat src_copy = g_src.clone();
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;
Mat src1, inpaintMask;
Point prevPt(-1, -1);

static void on_Mouse(int event, int x, int y, int flags, void*);
static void on_Mouse2(int event, int x, int y, int flags, void*);

int imageCountAndInpaint::helloworld() {
	printf("helloworld");
	Mat test = imread("1.jpg",1);
	imshow("12",test);
	char c = getchar();
	return 0;
}
int imageCountAndInpaint::findContoursTest()
{
	//����ͼ�����Ϊ��ֵͼ
	Mat src = imread("1.jpg", 0);
	//cvtColor(src, src, COLOR_BGR2GRAY);
	imshow("ԭʼͼ", src);

	//��ʼ�����ͼ
	Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);
	src = src > 119; //ȡ������ֵ119���ǲ���

	imshow("ȡ��ֵ���ԭʼͼ", src);

	//���������Ͳ�νṹ
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(src, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	int index = 0;
	for (; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dst, contours, index, color, FILLED, 8, hierarchy);
	}
	imshow("����ͼ", dst);
	waitKey(0);
	return 0;
}

void on_ThreshChange(int, void*) {
	//��ͼ����ж�ֵ����������ֵ
	threshold(g_gray, g_threshold_out, g_nTgresh, 255, THRESH_BINARY);

	//Ѱ������
	findContours(g_threshold_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//����ÿ��������Ѱ��͹��
	vector<vector<Point>> hull(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		convexHull(Mat(g_vContours[i]), hull[i], false);
	}
	Mat drawing = Mat::zeros(g_threshold_out.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}

	imshow(WINDOW_NAME2, drawing);

}

int imageCountAndInpaint::convexHullTest() {

	//����Դͼ��
	g_src = imread("1.jpg", 1);

	//��ԭͼתΪ�Ҷ�ͼ��
	cvtColor(g_src, g_gray, COLOR_BGR2GRAY);
	blur(g_gray, g_gray, Size(3, 3));

	//����ԭ���ڲ���ʾ
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_src);

	//����������
	createTrackbar("��ֵ", WINDOW_NAME1, &g_nTgresh, g_maxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);//����һ�ν��г�ʼ��

	waitKey(0);
	return(0);

}

int imageCountAndInpaint::findContoursEdge() {

	//��ʼ�����������ֵ
	Mat image(600, 600, CV_8UC3);
	RNG& rng = theRNG();

	while (1) {
		int count = rng.uniform(3, 103);
		vector<Point> points;

		//������������
		for (int i = 0; i < count; i++)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
			points.push_back(point);
		}

		//�Ը�����2D�㼯��Ѱ����С����İ�Χ����
		RotatedRect box = minAreaRect(Mat(points));
		Point2f vertex[4];
		box.points(vertex);
		image = Scalar::all(0);
		//���Ƴ������ɫ�ĵ�
		for (int i = 0; i < count; i++)
		{
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);
		}
		//���Ƴ���С����İ�Χ����
		for (int i = 0; i < 4; i++)
		{
			line(image, vertex[i], vertex[(i + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);
		}
		imshow("���ΰ�Χʾ��", image);

		Point2f center;
		float radius = 0;
		minEnclosingCircle(Mat(points), center, radius);
		circle(image, center, cvRound(radius), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, LINE_AA);
		imshow("Բ�κͰ�Χʾ��", image);
		char key = (char)waitKey();
		if (key == 27 || key == '1' || key == 'Q') //����q��Q��ESC�˳�
			break;
	}
	return 0;
}

void imageCountAndInpaint::watershedImageTest() {
	g_src = imread("1.jpg", 1);
	imshow("ԭͼ", g_src);
	Mat src, gray;
	g_src.copyTo(src);
	cvtColor(g_src, g_mask, COLOR_BGR2GRAY);
	cvtColor(g_mask, gray, COLOR_GRAY2BGR);
	g_mask = Scalar::all(0);

	//�������ص�����
	setMouseCallback("ԭͼ", on_Mouse, 0);

	//��ѯ����
	while (1) {
		char c = (char)waitKey();

		if (c == 27)
			break;
		if(c=='1'){
		int i, j, compCount = 0;
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		//Ѱ������
		findContours(g_mask, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

		//����Ϊ��
		if (contours.empty()) {
			continue;
		}
		Mat mask(g_mask.size(), CV_32S);
		mask = Scalar::all(0);
		//��������
		for (int index = 0; index >= 0; index = hierarchy[index][0],compCount++)
		{
			drawContours(mask, contours, index, Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);
		}
		if (compCount == 0)
			continue;

		//���������ɫ
		vector<Vec3b> clorTab;
		for (i = 0; i < compCount; i++)
		{
			int b = theRNG().uniform(0, 255);
			int g = theRNG().uniform(0, 255);
			int r = theRNG().uniform(0, 255);

			clorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
		}

		//���㴦��ʵ�����������
		double dTime = (double)getTickCount();

		watershed(src, mask);
		dTime = (double)getTickCount() - dTime;
		printf("\t����ʱ�� = %gms\n", dTime * 1000. / getTickFrequency());

		//����ˮ��ͼ���������wateredImage��
		Mat wateredImage(mask.size(), CV_8UC3);
		for (i = 0; i < mask.rows; i++)
		{
			for (j = 0; j < mask.cols; j++) {
				int index = mask.at<int>(i, j);

				if (index == -1)
					wateredImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
				else if (index <= 0 || index > compCount)
					wateredImage.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
				else
					wateredImage.at<Vec3b>(i, j) = clorTab[index - 1];
			}
		}
		//��ϻҶ�ͼ�ͷ�ˮ��Ч������ʾ���մ���
		wateredImage = wateredImage * 0.5 + gray * 0.5;
		imshow("��ˮ��Ч��", wateredImage);
	}
	}
}

void imageCountAndInpaint::imageInpaint() {
	Mat src = imread("2.jpg", -1);
	src1 = src.clone();
	inpaintMask = Mat::zeros(src1.size(), CV_8U);

	imshow("ԭͼ", src1);

	//�������ص�
	setMouseCallback("ԭͼ", on_Mouse2, 0);
	//��ѯ����
	while (1) {
		char c = (char)waitKey();

		if (c == 27)
			break;
		if (c == '1')
		{
			Mat inpaintedImage;
			inpaint(src1, inpaintMask, inpaintedImage, 3, INPAINT_TELEA);
			imshow("ͼ���޲�Ч��ͼ", inpaintedImage);
		}
	}
}

int imageCountAndInpaint::imreadImage() {
	Mat src = imread("1.jpg");
	imshow("����", src);
	waitKey(0);
	return 0;
}

static void on_Mouse(int event, int x, int y, int flags, void*) {

	if (x<0 || x>g_src.cols || y < 0 || y >= g_src.rows)
		return;

	//���������������Ϣ
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		prevPt = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)
		prevPt = Point(x, y);
	//���������¿�ʼ�ƶ������ư�ɫ����
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
		Point pt(x, y);
		if (prevPt.x < 0)
			prevPt = pt;
		line(g_mask, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(g_src, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow("ԭͼ", g_src);
	}
}

static void on_Mouse2(int event, int x, int y, int flags, void*) {
	//���������������Ϣ
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		prevPt = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)
		prevPt = Point(x, y);
	//���������¿�ʼ�ƶ������ư�ɫ����
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
		Point pt(x, y);
		if (prevPt.x < 0)
			prevPt = pt;
		line(inpaintMask, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(src1, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow("ԭͼ", src1);
	}
}