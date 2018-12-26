/*****************************************************************************
* 名称: APO_SeedSize.h
* 模块: XXX
* 描述: 用于返回种子大小比较的函数接口
*
* 作者: ParticularJ
* 日期: 2018.12.24
* 版本: 1.0
*
* Copyright (c) 2018.
* All rights reserved.
*****************************************************************************
*
* @change:
* @change:
*
*****************************************************************************/
#ifndef _API_SEEDSIZE_H_
#define _API_SEEDSIZE_H_

#ifdef SEEDSIZEDLL_EXPORTS
#define SEEDSIZEDLL _declspec(dllexport)
#else
#define SEEDSIZEDLL _declspec(dllexport)
#endif 
/*****************************************************************
** 函数功能：输出种子排序图
** 输入参数：src:种子的二值图， dst:种子的原图 //图像文件
** 输出结果：Mat 排序完成图 //检测线和对照线颜色深浅的比值
** 创建作者：ParticularJ
** 函数版本：1.0  2018.12.24
** 修改说明:
******************************************************************/
#include<opencv2/opencv.hpp>
#pragma warning(disable:4251)
class cmpH {
public:
	bool operator() (const std::pair<int, cv::RotatedRect> a, const std::pair<int, cv::RotatedRect> b) {
		float maxa = a.second.size.width > a.second.size.height ? a.second.size.width : a.second.size.height;
		float maxb = b.second.size.width > b.second.size.height ? b.second.size.width : b.second.size.height;
		return maxa < maxb;
	}
};

class cmpW {
public:
	bool operator() (const std::pair<int, cv::RotatedRect> a, const std::pair<int, cv::RotatedRect> b) {
		float maxa = a.second.size.width < a.second.size.height ? a.second.size.width : a.second.size.height;
		float maxb = b.second.size.width < b.second.size.height ? b.second.size.width : b.second.size.height;
		return maxa < maxb;
	}
};

class _declspec(dllexport)  plantInfo {
public:
	cv::Mat getImage(cv::Mat& src, cv::Mat& dst);
private:
	// 记录平均的长和宽
	int a, b;
	double avgHeight, avgWidth;
	// local 表示每次种子达到最底层越界时的修改参数
	// offset 表示右边种子的偏移量
	int local, offset;
	// 记录原图, 左原图，右原图
	cv::Mat dst_L, dst_R;
	// 每次长度足够，从新一行开始
	int new_line;

	// 记录有没有处理过该图
	std::vector<bool> flag;

	// 记录轮廓
	std::vector<std::vector<cv::Point>> contours;
	// 创立新图
	cv::Mat final_pic;
	// 记录heierarchy
	std::vector<cv::Vec4i> heierarchy;
	// 记录高
	std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH> myqueH;
	// 记录宽
	std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW> myqueW;
private:
	void sort_record(std::pair<int, cv::RotatedRect> &rect);
	std::pair<float, float> caculateAvg(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH> H);
	void findRect();
	void putROI(cv::Mat &roi, int flag);
	std::pair<cv::Point2f, cv::Point2f> caclAngle(float angle, cv::Point2f P[4], cv::Point2f &center);
	void get_rotMat(cv::RotatedRect& res, cv::Mat &rot_mat, cv::Point2f &center, float& angle, int flag);
	void displayHeight(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH>& myqueH, cv::Mat &dstH);
	void displayWidth(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW>& myqueW, cv::Mat &dstW);
	void SortSeed(cv::Mat &semi_src, cv::Mat &semi_dst);
};

#endif