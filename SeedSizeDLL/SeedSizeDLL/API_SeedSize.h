/*****************************************************************************
* ����: APO_SeedSize.h
* ģ��: XXX
* ����: ���ڷ������Ӵ�С�Ƚϵĺ����ӿ�
*
* ����: ParticularJ
* ����: 2018.12.24
* �汾: 1.0
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
** �������ܣ������������ͼ
** ���������src:���ӵĶ�ֵͼ�� dst:���ӵ�ԭͼ //ͼ���ļ�
** ��������Mat �������ͼ //����ߺͶ�������ɫ��ǳ�ı�ֵ
** �������ߣ�ParticularJ
** �����汾��1.0  2018.12.24
** �޸�˵��:
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
	// ��¼ƽ���ĳ��Ϳ�
	int a, b;
	double avgHeight, avgWidth;
	// local ��ʾÿ�����Ӵﵽ��ײ�Խ��ʱ���޸Ĳ���
	// offset ��ʾ�ұ����ӵ�ƫ����
	int local, offset;
	// ��¼ԭͼ, ��ԭͼ����ԭͼ
	cv::Mat dst_L, dst_R;
	// ÿ�γ����㹻������һ�п�ʼ
	int new_line;

	// ��¼��û�д������ͼ
	std::vector<bool> flag;

	// ��¼����
	std::vector<std::vector<cv::Point>> contours;
	// ������ͼ
	cv::Mat final_pic;
	// ��¼heierarchy
	std::vector<cv::Vec4i> heierarchy;
	// ��¼��
	std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH> myqueH;
	// ��¼��
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