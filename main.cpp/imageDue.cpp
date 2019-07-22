#include"imageDue.h"
//Canny边缘检测及其高级应用
int imageDue::edgeCheck() {
	//载入图像
	Mat src = imread("1.jpg");
	Mat src1 = src.clone();//完全拷贝，把src的所有信息拷贝到src1中

	imshow("【原始图】Canny边缘检测", src);
	//拿到图像直接canny边缘检测已被opencv3弃用
	Canny(src, src, 150, 100, 3);
	imshow("【效果图】Canny边缘检测", src);

	//Canny高阶操作

	Mat dst, edge, gray;
	//创建于src大小相等的矩阵(数据区）
	dst.create(src1.size(), src1.type());
	//将图像转换为灰度图像
	cvtColor(src1, gray, COLOR_BGR2GRAY);

	imshow("【灰度图像】", gray);

	//使用3x3内核降噪
	blur(gray, edge, Size(3, 3));
	imshow("【灰度图像降噪后】", edge);

	Canny(edge, edge, 3, 9, 3);
	imshow("【灰度图像边缘检测】", edge);

	src1.copyTo(dst, edge);
	imshow("【彩色边缘检测效果】", dst);
	waitKey(0);
	return 0;
}

int imageDue::sobelEdge() {

	//创建梯度方向为x、y的矩阵
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	//载入图像
	Mat src = imread("1.jpg");
	imshow("【原图】", src);

	Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("【x方向Sobel】", abs_grad_x);

	Sobel(src, grad_y, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);//图像增强
	imshow("【y方向Sobel】", abs_grad_y);

	//合并梯度
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("【合并梯度效果】", dst);

	waitKey(0);
	return 0;
}

//霍夫变换(此函数绘制有问题）
int imageDue::hougLines() {
	Mat src = imread("1.jpg");
	Mat mid, dis;
	//经过边缘检测和灰度处理才能得到8位单通道二进制图像
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
	imshow("原始图", src);

	imshow("边缘检测图", mid);

	imshow("霍夫变换图", dis);

	waitKey(0);
	return 0;
}
//
int imageDue::hougLinesP() {

	Mat src = imread("1.jpg");
	Mat mid, dis;
	//经过边缘检测和灰度处理才能得到8位单通道二进制图像
	Canny(src, mid, 50, 200, 3);
	cvtColor(mid, dis, COLOR_GRAY2BGR);
	vector<Vec4i> lines;
	HoughLinesP(mid, lines, 1, CV_PI / 180, 80, 50, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];

		line(dis, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255));

	}
	imshow("原始图", src);

	imshow("边缘检测图", mid);

	imshow("霍夫变换图", dis);

	waitKey(0);
	return 0;
}
//图像重映射
int imageDue::remapImage() {
	Mat src, dst;
	Mat map_x, map_y;
	src = imread("1.jpg", 1);
	dst = imread("1.jpg");
	imshow("原始图", src);
	imshow("原始图", dst);
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
	imshow("重映射", dst);
	waitKey(0);
	return 0;
}

int imageDue::equalHist() {
	Mat src, dst;
	src = imread("1.jpg", 1);
	cvtColor(src, src, COLOR_BGR2GRAY);
	imshow("灰度图像", src);

	equalizeHist(src, dst);
	imshow("直方均衡化", dst);
	waitKey(0);
	return 0;
}