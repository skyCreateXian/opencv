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
				Point(hue * scale, saturation * scale),
				Point((hue + 1) * scale - 1,
				(saturation + 1) * scale - 1),
				Scalar::all(intensity),
				FILLED
			);
		}
	}
	imshow("原图", src);
	imshow("H-S直方图", histImg);
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
