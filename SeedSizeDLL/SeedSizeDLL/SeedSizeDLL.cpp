// SeedSizeDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "API_SeedSize.h"
#include<opencv2/opencv.hpp>

#define PI 3.14

cv::Mat plantInfo::getImage(cv::Mat& src, cv::Mat& dst) {
	// 初始化最终的结果图
	plantInfo::final_pic = cv::Mat(cv::Size(src.rows, src.cols), CV_8UC3, cv::Scalar(0, 0, 0));
	// 初始化记录长的位置
	plantInfo::local = 0;
	plantInfo::offset = 0;
	//获得一半图
	cv::Rect rect_l, rect_r;
	rect_l = cv::Rect(0, 0, src.cols / 2, src.rows);
	rect_r = cv::Rect(src.cols / 2, 0, src.cols - src.cols / 2, src.rows);

	// 获取左半张图
	cv::Mat img_L = src(rect_l);
	plantInfo::dst_L = dst(rect_l);
	SortSeed(img_L, dst_L);


	// 清空队列
	while (!myqueH.empty()) {
		myqueH.pop();
	}
	while (!myqueW.empty()) {
		myqueW.pop();
	}

	plantInfo::local = 0;
	plantInfo::offset = src.cols / 2;
	// 获取右半张图
	cv::Mat img_R = src(rect_r);
	plantInfo::dst_R = dst(rect_r);
	SortSeed(img_R, dst_R);
	return final_pic;
}

void plantInfo::sort_record(std::pair<int, cv::RotatedRect> &rect) {
	myqueW.push(rect);
	myqueH.push(rect);
}


std::pair<float, float> plantInfo::caculateAvg(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH> H) {
	float height = 0;
	float width = 0;
	size_t size = H.size();
	for (int i = 0; i < 10; i++) {
		H.pop();
	}
	while (!H.empty()) {
		cv::RotatedRect res = H.top().second;
		float h = std::max(res.size.height, res.size.width);
		float w = std::min(res.size.height, res.size.width);
		height += h;
		width += w;
		H.pop();
	}
	return std::make_pair(height / size, width / size);
}

void plantInfo::findRect() {
	for (int i = 0; i < contours.size(); i++) {
		cv::RotatedRect rect = minAreaRect(contours[i]);
		// rect.boundingRect
		// 分别对高和宽进行排序
		sort_record(std::make_pair(i, rect));
	}
}

void plantInfo::putROI(cv::Mat &roi, int flag) {
	cv::Mat roi_img;

	if (local + roi.rows < final_pic.rows) {
		if (flag == 0)
			roi_img = (final_pic(cv::Range(local, local + roi.rows), cv::Range(0 + offset, offset + roi.cols)));
		else {
			roi_img = (final_pic(cv::Range(local, local + roi.rows), cv::Range(offset + static_cast<int>(avgHeight) * 2 + static_cast<int>(avgWidth), offset + static_cast<int>(avgHeight) * 2 + static_cast<int>(avgWidth) + roi.cols)));
		}
	}
	else {
		if (flag == 0) {
			roi_img = (final_pic(cv::Range(new_line, roi.rows + new_line), cv::Range(offset + static_cast<int>(avgHeight), offset + static_cast<int>(avgHeight) + roi.cols)));
			new_line += roi.rows;
		}
		else {
			roi_img = (final_pic(cv::Range(new_line, roi.rows + new_line), cv::Range(offset + static_cast<int>(avgHeight) * 3 + static_cast<int>(avgWidth), offset + static_cast<int>(avgHeight) * 3 + static_cast<int>(avgWidth) + roi.cols)));
			new_line += roi.rows;
		}
	}
	roi.copyTo(roi_img);
	local += roi.rows;
}


std::pair<cv::Point2f, cv::Point2f> plantInfo::caclAngle(float angle, cv::Point2f P[4], cv::Point2f &center) {
	// 计算旋转之后P[0]与P[2]的坐标
	cv::Point2f Q[2];
	float angle_arc = static_cast<float>(PI / 180.0 * angle);

	//  绕某个中心的旋转公式
	Q[0].x = (P[0].x - center.x)*cos(angle_arc) - (center.y - P[0].y)*sin(angle_arc) + center.x;
	Q[0].y = center.y - (P[0].x - center.x)*sin(angle_arc) - (center.y - P[0].y)*cos(angle_arc);
	Q[1].x = (P[2].x - center.x)*cos(angle_arc) - (center.y - P[2].y)*sin(angle_arc) + center.x;
	Q[1].y = center.y - (P[2].x - center.x)*sin(angle_arc) - (center.y - P[2].y)*cos(angle_arc);
	return std::make_pair(Q[0], Q[1]);
}

void plantInfo::get_rotMat(cv::RotatedRect& res, cv::Mat &rot_mat, cv::Point2f &center, float& angle, int flag) {
	if (flag == 0) {
		if (res.size.width > res.size.height) {
			if (res.angle != 0) {
				angle = 90 + res.angle;
				rot_mat = getRotationMatrix2D(center, angle, 1);
			}
			else {
				angle = 90;
				rot_mat = getRotationMatrix2D(center, angle, 1);
			}

		}
		else {
			if (res.angle != 0) {
				angle = res.angle;
				rot_mat = getRotationMatrix2D(center, angle, 1);
			}
			else {
				rot_mat = getRotationMatrix2D(center, angle, 1);
			}
		}
	}
	else {
		if (res.size.width < res.size.height) {
			if (res.angle != 0) {
				angle = (90 + res.angle);
				rot_mat = getRotationMatrix2D(center, angle, 1);
			}
			else {
				angle = 90;
				rot_mat = getRotationMatrix2D(center, angle, 1);
			}

		}
		else {
			if (res.angle != 0) {
				angle = res.angle;
				rot_mat = getRotationMatrix2D(center, angle, 1);
			}
			else {
				angle = 0;
				rot_mat = getRotationMatrix2D(center, angle, 1);
			}
		}
	}
}


void plantInfo::displayHeight(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH>& myqueH, cv::Mat &dstH) {
	// 初始化顶格后新的行
	new_line = 0;

	for (int i = 0; i < 20; i++) {
		// 拷贝一份新图
		cv::Mat dst1 = dstH.clone();
		std::pair<int, cv::RotatedRect> front = myqueH.top();
		//	取出最大的数据
		cv::RotatedRect res = front.second;
		// 轮廓的位置坐标
		int ConNum = front.first;
		cv::Point2f P[4];
		res.points(P);
		myqueH.pop();

		const float height = std::max(res.size.height, res.size.width);
		const float width = std::min(res.size.height, res.size.width);


		if (abs(height - avgHeight) > avgHeight / 1.5 || abs(width - avgWidth) > avgWidth / 3) {
			i--;
			continue;
		}
		// 旋转图像
		// 定义旋转矩阵
		cv::Mat rot_mat;
		float angle = 0;

		// 测试分割开旋转，截取
		cv::Mat mask, seg_mat, seg_final;
		mask = dst1(cv::Rect(res.boundingRect().tl(), res.boundingRect().br()));
		seg_mat = mask.clone();
		int off_x = res.boundingRect().tl().x;
		int off_y = res.boundingRect().tl().y;

		for (int i = 0; i < contours[ConNum].size(); i++) {
			contours[ConNum][i].x -= off_x;
			contours[ConNum][i].y -= off_y;
		}
		flag[ConNum] = 1;

		drawContours(mask, contours, ConNum, cv::Scalar(255, 255, 255), -1);
		cvtColor(mask, mask, CV_RGB2GRAY);
		threshold(mask, mask, 254, 255, cv::THRESH_BINARY);
		mask.convertTo(mask, CV_8UC3);
		seg_mat.copyTo(seg_final, mask);

		int border = 70;
		copyMakeBorder(seg_final, seg_final, border, border, border, border, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));


		// 得到旋转矩阵和旋转角度
		cv::Point2f center;
		center.x = res.center.x - off_x + border;
		center.y = res.center.y - off_y + border;

		get_rotMat(res, rot_mat, center, angle, 0);
		P[0].x -= (off_x - border);
		P[0].y -= (off_y - border);
		P[2].x -= (off_x - border);
		P[2].y -= (off_y - border);
		std::pair<cv::Point2f, cv::Point2f> Q_t = caclAngle(angle, P, center);

		cv::Mat test_rot;
		warpAffine(seg_final, test_rot, rot_mat, seg_final.size());
		cv::Mat final_test;
		final_test = test_rot(cv::Rect(Q_t.first, Q_t.second));
		putROI(final_test, 0);
	}
}

void plantInfo::displayWidth(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW>& myqueW, cv::Mat &dstW) {
	// 重置记录长度，判断是否顶格，使之从0开始
	local = 0;
	// 初始化顶格后的长度
	new_line = 0;
	for (int i = 0; i < 20; i++) {
		cv::Mat dst1 = dstW.clone();
		// 记录信息
		std::pair<int, cv::RotatedRect> front = myqueW.top();
		// 旋转矩阵信息
		cv::RotatedRect res = front.second;
		// contours 信息
		int ConNum = front.first;
		cv::Point2f P[4];
		res.points(P);
		myqueW.pop();

		const float height = std::max(res.size.height, res.size.width);
		const float width = std::min(res.size.height, res.size.width);

		if (abs(height - avgHeight) > avgHeight / 3 || abs(width - avgWidth) > avgWidth / 2) {
			i--;
			continue;
		}


		cv::Mat rot_mat;
		float angle = 0;

		cv::Mat mask, seg_mat, seg_final;
		mask = dst1(cv::Rect(res.boundingRect().tl(), res.boundingRect().br()));
		seg_mat = mask.clone();
		int off_x = res.boundingRect().tl().x;
		int off_y = res.boundingRect().tl().y;

		if (!flag[ConNum]) {
			for (int i = 0; i < contours[ConNum].size(); i++) {
				contours[ConNum][i].x -= off_x;
				contours[ConNum][i].y -= off_y;
			}
		}


		drawContours(mask, contours, ConNum, cv::Scalar(255, 255, 255), -1);

		cvtColor(mask, mask, CV_RGB2GRAY);
		threshold(mask, mask, 254, 255, cv::THRESH_BINARY);

		mask.convertTo(mask, CV_8UC3);
		seg_mat.copyTo(seg_final, mask);

		int border = 70;
		copyMakeBorder(seg_final, seg_final, border, border, border, border, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));


		// 得到旋转矩阵和旋转角度
		cv::Point2f center;
		center.x = res.center.x - off_x + border;
		center.y = res.center.y - off_y + border;

		get_rotMat(res, rot_mat, center, angle, 1);
		P[0].x -= (off_x - border);
		P[0].y -= (off_y - border);
		P[2].x -= (off_x - border);
		P[2].y -= (off_y - border);
		std::pair<cv::Point2f, cv::Point2f> Q_t = caclAngle(angle, P, center);

		cv::Mat test_rot;
		warpAffine(seg_final, test_rot, rot_mat, seg_final.size());
		cv::Mat final_test;
		final_test = test_rot(cv::Rect(Q_t.first, Q_t.second));
		putROI(final_test, 1);
	}
}
void plantInfo::SortSeed(cv::Mat &semi_src, cv::Mat &semi_dst) {
	cv::Mat gray;
	// convert to gray
	cv::cvtColor(semi_src, gray, CV_RGB2GRAY);
	cv::GaussianBlur(gray, gray, cv::Size(3, 3), 0, 0);
	// convert to binary
	cv::threshold(gray, gray, 135, 255, cv::THRESH_BINARY);
	// RETR_CCOMP record outer and holes
	// CHAIN_APPROX_SIMPLE record conor points
	cv::findContours(gray, contours, heierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
	// 寻找外轮廓
	// 寻找外接矩形
	findRect();
	// 获得平均的高和宽
	std::pair<float, float> avg = caculateAvg(myqueH);
	avgHeight = avg.first;
	avgWidth = avg.second;
	plantInfo::flag = std::vector<bool>(contours.size(), false);
	displayHeight(myqueH, semi_dst);
	displayWidth(myqueW, semi_dst);
}




