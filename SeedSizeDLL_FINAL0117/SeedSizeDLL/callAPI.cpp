#include"callDLL.h"

/*
	C++ 接口
	可以直接传入C#的参数，通过此函数转为C++代码所需的参数类型
parameters:
	src_data: 种子的二值图数据
	src_width: 二值图的宽
	src_height: 二值图的高
	src_step: 二值图的步长
	dst_data: 种子的原图数据
	dst_width : 原图的宽
	dst_height: 原图的高
	dst_step: 原图的步长
	pfinal_pic: 得到图的data指针
*/


// seedNum 种子个数
// sortByHeightOrWidth: true按照长排，false按照宽排 

int __stdcall simuStr(SeedInfo *seedInfo) {
	plantInfo seed;
	seed.simuStr(seedInfo);
	return 1;
}

int __stdcall getImage(int seedNum, bool sortByHeightOrWidth, uchar* src_data, int src_width, int src_height, int src_step, uchar* dst_data, int dst_width, int dst_height, int dst_step, uchar* pfinal_pic, SeedInfo* seedInfo) {
	
	plantInfo seed(seedNum, sortByHeightOrWidth);
	
	// 建立src对应二值图，
	// dst 对应原图
	// SeedSizeImg 对应种子排序大小图
	cv::Mat src(src_height, src_width, CV_8UC1, src_data, src_step);
	cv::Mat dst(dst_height, dst_width, CV_8UC3, dst_data, dst_step);
	cv::Mat SeedSizeImg;
	// 获得种子大小图
	/*cv::imshow("src", src);
	cv::waitKey(0);
	cv::imshow("dst", dst);
	cv::waitKey(0);*/

	int res = seed.getImage(src, dst, SeedSizeImg, seedInfo);
	
	cv::cvtColor(SeedSizeImg, SeedSizeImg, CV_BGR2BGRA);

	// 获取final所需的内存
	int size = 4 * SeedSizeImg.rows*SeedSizeImg.cols;
	// 将得到的mat图拷贝一份
	memcpy(pfinal_pic, SeedSizeImg.data, size);
	return 1;
}

