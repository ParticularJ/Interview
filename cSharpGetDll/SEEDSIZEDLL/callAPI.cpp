#include"callDLL.h"

/*
C++ 接口
可以直接传入C#的参数，通过此函数转为C++代码所需的参数类型
parameters:
dst_data: 种子的原图数据
dst_width : 原图的宽
dst_height: 原图的高
dst_step: 原图的步长
pfinal_pic: 得到图的data指针
*/


// seedNum 种子个数

int __stdcall getImage(int seedNum, uchar* dst_data, int dst_width, int dst_height, int dst_step, uchar* pfinal_pic, SeedInfo* seedInfo) {
	// 初始化类
	plantInfo seed(seedNum);

	// 建立src对应二值图，
	// dst 对应原图
	// SeedSizeImg 对应种子排序大小图
	cv::Mat src(dst_height, dst_width, CV_8UC1, cv::Scalar(0));
	// cv::Mat src = cv::imread("5.jpg", 0);
	cv::Mat dst(dst_height, dst_width, CV_8UC3, dst_data, dst_step);
	cv::Mat SeedSizeImg;
	// 获得种子大小图
	/*cv::imshow("src", src);
	cv::waitKey(0);
	cv::imshow("dst", dst);
	cv::waitKey(0);*/


	for (int i = 0; i < 2000; i++) {
		// 轮廓
		std::vector<std::vector<cv::Point>> contours(2000, std::vector<cv::Point>());
		if (seedInfo[i].sLength == 0 && seedInfo[i].sWide == 0)
			break;
		else {
			for (int j = 0; j < 250; j++) {
				if (seedInfo[i].contour[j].x == 0 && seedInfo[i].contour[j].y == 0)
					break;
				contours[i].push_back(cv::Point(seedInfo[i].contour[j].x, seedInfo[i].contour[j].y));
			}

			// 若点为（0， 0）,跳出循环
			cv::drawContours(src, contours, i, cv::Scalar(255), -1);
		}
	}

	cv::imwrite("./binary.jpg", src);
	//	cv::imwrite("./ori.jpg", dst);


	int res = seed.getImage(src, dst, SeedSizeImg, seedInfo);

	cv::cvtColor(SeedSizeImg, SeedSizeImg, CV_BGR2BGRA);

	// 获取final所需的内存
	int size = 4 * SeedSizeImg.rows*SeedSizeImg.cols;
	// 将得到的mat图拷贝一份
	memcpy(pfinal_pic, SeedSizeImg.data, size);
	return 1;
}


