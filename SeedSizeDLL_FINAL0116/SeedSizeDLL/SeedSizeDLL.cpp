// SeedSizeDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include"API_SeedSize.h"

#define PI 3.14

// 记录高
std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH> myqueH;
// 记录宽
std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW> myqueW;
// 记录有没有处理过该图
std::vector<bool> flag;


/*
	parameters:
	src: 二值图
	dst: 原图
	final_pic: 最终的结果图
	seedInfo: 种子信息的结构体
*/





int plantInfo::getImage(cv::Mat &src, cv::Mat &dst, cv::Mat &final_pic, SeedInfo* seedInfo) {
	final_pic = cv::Mat(cv::Size(dst.cols, dst.rows), CV_8UC3, cv::Scalar(0, 0, 0));
	// 初始化最终的结果图
	// plantInfo::final_pic = cv::Mat(cv::Size(800, 600), CV_8UC3, cv::Scalar(0, 0, 0));
	// 初始化记录长的位置
	plantInfo::local = 0;
	plantInfo::offset = 0;
	// 初始化结构体指针
	plantInfo::seed_global = seedInfo;


	//获得一半图
	cv::Rect rect_l, rect_r;
	rect_l = cv::Rect(0, 0, src.cols / 2, src.rows);
	rect_r = cv::Rect(src.cols / 2, 0, src.cols - src.cols / 2, src.rows);
	plantInfo::segloc = src.cols / 2;
	// 获取左半张图
	cv::Mat img_L = src(rect_l);
	cv::Mat dst_L = dst(rect_l);

	

	SortSeed(img_L, dst_L, final_pic);
	

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
	cv::Mat dst_R = dst(rect_r);
	SortSeed(img_R, dst_R, final_pic);
	return 1;
}

// 优先队列长和宽
/*
	int : 当前种子的ID
	rect: 种子的信息，旋转角度，外接矩形等
*/
void plantInfo::sort_record(std::pair<int, cv::RotatedRect> &rect) {
	myqueW.push(rect);
	myqueH.push(rect);
}


// 计算平均的长和宽
std::pair<float, float> plantInfo::caculateAvg(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH> H) {
	float height = 0;
	float width = 0;
	size_t size = H.size();
	int pop_size = static_cast<int>(H.size() * 0.2);
	for (int i = 0; i < pop_size; i++) {
		H.pop();
	}
	while (H.size()-pop_size!=0) {
		cv::RotatedRect res = H.top().second;
		float h = std::max(res.size.height, res.size.width);
		float w = std::min(res.size.height, res.size.width);
		height += h;
		width += w;
		H.pop();
	}
	return std::make_pair(height / (size - 2 * pop_size), width / (size - 2 * pop_size));
}

// 寻找外接矩形
void plantInfo::findRect(std::vector<std::vector<cv::Point>>& contours) {
	for (size_t i = 0; i < contours.size(); i++) {
		cv::RotatedRect rect = minAreaRect(contours[i]);
		// rect.boundingRect
		// 分别对高和宽进行排序
		sort_record(std::make_pair(static_cast<int>(i), rect));
	}
}


// 将结果放置一张图上
void plantInfo::putROI(cv::Mat &roi, cv::Mat &final_pic, int flag, int ID) {
	cv::Mat roi_img;

	if (local + roi.rows < final_pic.rows) {
		if (flag == 0) {
			roi_img = (final_pic(cv::Range(local, local + roi.rows), cv::Range(0 + offset, offset + roi.cols)));
			putText(final_pic, "ID:" + std::to_string(ID), cv::Point(offset + roi.cols + 10, (local + roi.rows)), 2, 1, cv::Scalar(255, 0, 0), 2);
		}
		else {
			roi_img = (final_pic(cv::Range(local, local + roi.rows), cv::Range(offset + static_cast<int>(avgHeight) * 3 + static_cast<int>(avgWidth),
						offset + static_cast<int>(avgHeight) * 3 + static_cast<int>(avgWidth) + roi.cols)));
			putText(final_pic, "ID:" + std::to_string(ID), cv::Point(offset + static_cast<int>(avgHeight) * 3 + static_cast<int>(avgWidth) + roi.cols + 10, 
					(local + roi.rows)), 2, 1, cv::Scalar(255, 0, 0), 2);
		}
	}
	else {
		if (flag == 0) {
			roi_img = (final_pic(cv::Range(new_line, roi.rows + new_line), cv::Range(offset + 2 * static_cast<int>(avgHeight), offset + 2 * static_cast<int>(avgHeight) + roi.cols)));
			putText(final_pic, "ID:" + std::to_string(ID), cv::Point(offset + 2 * static_cast<int>(avgHeight) + roi.cols + 10, (roi.rows + new_line)), 2, 1, cv::Scalar(255, 0, 0), 2);
			new_line += (roi.rows + 20);
		}
		else {
			roi_img = (final_pic(cv::Range(new_line, roi.rows + new_line), cv::Range(offset + 2 * static_cast<int>(avgHeight) * 3, offset + 2 * static_cast<int>(avgHeight) * 3 + roi.cols)));
			putText(final_pic, "ID:" + std::to_string(ID), cv::Point(offset + 2 * static_cast<int>(avgHeight) * 3 + roi.cols + 10, (roi.rows + new_line)), 2, 1, cv::Scalar(255, 0, 0), 2);
			new_line += (roi.rows + 20);
		}
	}
	roi.copyTo(roi_img);
	local += (roi.rows + 20);
}


// 计算旋转后的点坐标
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

// 获得旋转矩阵
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

// 按照高进行排序
void plantInfo::displayHeight(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH>& myqueH, cv::Mat &dstH,
								cv::Mat &final_pic, std::vector<std::vector<cv::Point>>& contours) {
	// 初始化顶格后新的行
	new_line = 0;

	for (int i = 0; i < 20; i++) {
		// 拷贝一份新图
		cv::Mat dst1 = dstH.clone();
		//	取出最大的数据
		std::pair<int, cv::RotatedRect> front = myqueH.top();

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



		// 确定真实的ID坐标
		int real_ID = 0;
		for (size_t i = 0; i < contours.size(); i++) {
			int real_x = seed_global[i].centerPt.x > segloc ? seed_global[i].centerPt.x - segloc : seed_global[i].centerPt.x;
			int real_y = seed_global[i].centerPt.y;
			if (static_cast<int>(res.center.x) == real_x && static_cast<int>(res.center.y) == real_y) {
				real_ID = seed_global[i].ID;
				break;
			}
			else
				real_ID = -1;
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

		for (size_t i = 0; i < contours[ConNum].size(); i++) {
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
		putROI(final_test, final_pic, 0, real_ID);
	}
}


// 按照宽进行排序
void plantInfo::displayWidth(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW>& myqueW, cv::Mat &dstW, 
									cv::Mat &final_pic, std::vector<std::vector<cv::Point>>& contours) {
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
		
		// 确定真实的ID坐标
		// 确定真实的ID坐标
		int real_ID = 0;
		for (size_t i = 0; i < contours.size(); i++) {
			int real_x = seed_global[i].centerPt.x > segloc ? seed_global[i].centerPt.x - segloc : seed_global[i].centerPt.x;
			int real_y = seed_global[i].centerPt.y;
			if (static_cast<int>(res.center.x) == real_x && static_cast<int>(res.center.y) == real_y) {
				real_ID = seed_global[i].ID;
				break;
			}
			else
				real_ID = -1;
		}

		cv::Mat rot_mat;
		float angle = 0;

		cv::Mat mask, seg_mat, seg_final;
		mask = dst1(cv::Rect(res.boundingRect().tl(), res.boundingRect().br()));
		seg_mat = mask.clone();
		int off_x = res.boundingRect().tl().x;
		int off_y = res.boundingRect().tl().y;

		if (!flag[ConNum]) {
			for (size_t i = 0; i < contours[ConNum].size(); i++) {
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
		putROI(final_test, final_pic, 1, real_ID);
	}
}


// 分别对每一半图像进行种子排序
void plantInfo::SortSeed(cv::Mat &semi_src, cv::Mat &semi_dst, cv::Mat & final_pic) {
	cv::Mat gray;
	// convert to gray
	//cv::cvtColor(semi_src, gray, CV_RGB2GRAY);
	//cv::GaussianBlur(gray, gray, cv::Size(3, 3), 0, 0);
	// convert to binary
	cv::threshold(semi_src, gray, 135, 255, cv::THRESH_BINARY);
	// RETR_CCOMP record outer and holes
	// CHAIN_APPROX_SIMPLE record conor points
	// 记录轮廓
	std::vector<std::vector<cv::Point>> contours;

	// 记录heierarchy
	std::vector<cv::Vec4i> heierarchy;

	cv::findContours(gray, contours, heierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	// 寻找外轮廓
	// 寻找外接矩形
	findRect(contours);
	// 获得平均的高和宽
	std::pair<float, float> avg = caculateAvg(myqueH);
	avgHeight = avg.first;
	avgWidth = avg.second;
	flag = std::vector<bool>(contours.size(), false);
	displayHeight(myqueH, semi_dst, final_pic, contours);
	displayWidth(myqueW, semi_dst, final_pic, contours);
}


void plantInfo::simuStr(SeedInfo *seedInfo) {
	seedInfo[0].ID = 1;
	seedInfo[0].centerPt.x = 205;
	seedInfo[0].centerPt.y = 1714;

	seedInfo[1].ID = 2;
	seedInfo[1].centerPt.x = 738;
	seedInfo[1].centerPt.y = 1494;


	seedInfo[2].ID = 3;
	seedInfo[2].centerPt.x = 773;
	seedInfo[2].centerPt.y = 780;


	seedInfo[3].ID = 4;
	seedInfo[3].centerPt.x = 826;
	seedInfo[3].centerPt.y = 1252;
}



