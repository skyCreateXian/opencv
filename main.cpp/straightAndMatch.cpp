#include"straightAndMatch.h"

void straightAndMatch::paintHSMap()
{
	//载入图像，转化为HSV模式
	Mat src, hsv;
	src = imread("1.jpg");
	cvtColor(src, hsv, COLOR_BGR2HSV);

	//将色调调量化为30个等级，将饱和和度量化为32个等级
	int hueBinNum = 30;//色调的直方图直条数量
	int sat = 32;
	int hist[] = { hueBinNum,sat };//将hue、sat放入数组

	//定义色调的变化范围为0到179
	float hueRanges[] = { 0,180 };
	//定义饱和度的变化范围为0（黑白灰）到255（纯光谱颜色）
	float satRanges[] = { 0,255 };

	const float* ranges[] = { hueRanges,satRanges };
	//MatND用于存储直方图的一种数据结构
	MatND dstHist;
	//calcHist函数中将计算第0通道和第一通道的直方图

	int channels[] = { 0,1 };

	//调用calcHist，进行直方图计算
	calcHist(&hsv,//输入数组
		1,//数组个数
		channels,//通道索引
		Mat(),//不使用掩模
		dstHist,//输出的目标直方图
		2,//需要巨酸的直方图的维度为2
		hist,//存放每个维度的直方图尺寸的数组
		ranges,//每一维的取值范围数组
		true,//指示直方图是否均匀的标识符
		false);//累计标识符，f表示直方图在匹配阶段会被清0
	
	//绘制直方图需要参数
	double maxValue = 0;//最大值
	//在数组中找到全局最小值和最大值
	minMaxLoc(dstHist,//输入阵列
		0,//无返回最小指针
		&maxValue,//返回最大指针
		0,//无返回最小位置的指针
		0);//无返回最大位置的指针
	//最后一个参数可选，用于子阵列的可选掩膜

	int scale = 10;
	//创建一张行为第一个参数，列为第二个参数，类型为第三个参数的空白图像
	Mat histImg = Mat::zeros(sat * scale, hueBinNum * 10, CV_8UC3);

	for ( int hue = 0; hue < hueBinNum; hue++)//遍历色调
	{
		for (int saturation = 0; saturation < sat; saturation++) {//遍历饱和度
			float binValue = dstHist.at<float>(hue, saturation);//访问图像像素
			int intensity = cvRound(binValue * 255 / maxValue);//强度
			//长方形绘制函数
			rectangle(
				histImg,
				Point(hue * scale, saturation * scale),//矩形上对角点
				Point((hue + 1) * scale - 1,//矩形下对角点
				(saturation + 1) * scale - 1),
				Scalar::all(intensity),//举行颜色
				FILLED//线的厚度
			);
		}
	}
	imshow("原图", src);
	imshow("H-S直方图", histImg);
	waitKey();
}

void straightAndMatch::paintOneMap()
{
	Mat src = imread("1.jpg");
	imshow("原图", src);

	MatND dstHist;
	int dims = 1;
	float hranges[] = { 0,255 };
	const float *ranges[] = { hranges };//const类型只读，const类型博大精深，在这里理解为只读
	int size = 256;
	int channels = 0;

	//计算图像直方图
	calcHist(&src,//输入数组
		1,//输入数组个数
		&channels,//需要统计的通道索引
		Mat(),//掩码
		dstHist,//输出数组
		dims,//直方图维度
		&size,//存放每个维度的直方图尺寸的数组
		ranges);//每个维度取值范围
	int scale = 1;
	Mat dstImg(size * scale, size, CV_8U, Scalar(0));//生成256*256的灰度图像

	double maxValue = 0;
	double minValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);//查找数组和子数组的全局最小值和最大值存入maxValue
	
	//绘制直方图
	int hpt = saturate_cast<int>(0.9 * size);//取整==cvRound
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);//访问像素值
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);//像素同步缩小，使最大像素值为1
		rectangle(dstImg, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realValue), Scalar(255));
	}
	imshow("一维直方图", dstImg);
	waitKey(0);

}

void straightAndMatch::paintThreeMap()
{
	Mat src;
	src = imread("1.jpg");
	imshow("原图", src);

	//参数
	int bins = 256;
	int hist_size[] = { bins };
	float range[] = { 0,256 };
	const float* ranges[] = { range };
	MatND redHist, grayHist, blueHist;

	//直方图的计算 三色
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

	//绘制
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

	//在窗口中显示出绘制好的直方图
	imshow("图像中的RGBz直方图", histImg);
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
