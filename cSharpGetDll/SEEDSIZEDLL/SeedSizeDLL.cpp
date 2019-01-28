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


// 记录轮廓
std::vector<std::vector<cv::Point>> contours;

// 记录heierarchy
std::vector<cv::Vec4i> heierarchy;

// 记录凸包
std::vector<std::vector<cv::Point> > hull;

/*
parameters:
src: 二值图
dst: 原图
final_pic: 最终的结果图
seedInfo: 种子信息的结构体
*/


plantInfo::plantInfo() {}

plantInfo::plantInfo(int seed) :seedNum(seed), totalHeight(0), totalWidth(0), top_X(0), top_Y(0), bottom_X(0), bottom_Y(0), offsetw(0), offseth(0), offset_seed(0) {}

plantInfo::~plantInfo() {}
int plantInfo::getImage(cv::Mat &src, cv::Mat &dst, cv::Mat &final_pic, SeedInfo* seedInfo) {
	final_pic = cv::Mat(cv::Size(3469, 2518), CV_8UC3, cv::Scalar(255, 255, 255));
	//	cv::imwrite("final.jpg", final_pic);
	// 清空队列
	while (!myqueH.empty()) {
		myqueH.pop();
	}
	while (!myqueW.empty()) {
		myqueW.pop();
	}


	// 初始化最终的结果图
	// 初始化记录长的位置
	plantInfo::local = 20;
	plantInfo::offset = 20;
	// 初始化结构体指针
	plantInfo::seed_global = seedInfo;

	// 获得平均的高和宽
	avgHeight = 0;
	avgWidth = 0;
	avgArea = 0;
	offsetw = 0;
	offseth = 0;


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

	// 重新初始化总高和总宽
	totalWidth = 0;
	totalHeight = 0;
	offset_seed = segloc;

	plantInfo::local = 20;
	plantInfo::offsetw = 870;
	plantInfo::offseth = 870;
	plantInfo::offset += offseth;
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
std::pair<std::pair<float, float>, float> plantInfo::caculateAvg(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH> H,
	std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW> W) {
	float height = 0;
	float width = 0;
	float area = 0;
	size_t size = H.size();
	int pop_size = static_cast<int>(H.size() * 0.2);
	for (int i = 0; i < pop_size; i++) {
		H.pop();
		W.pop();
	}
	while (H.size() - pop_size != 0) {
		cv::RotatedRect res = H.top().second;
		float h = std::max(res.size.height, res.size.width);
		area += cv::contourArea(contours[H.top().first], false);
		height += h;
		H.pop();
	}
	while (W.size() - pop_size != 0) {
		cv::RotatedRect res = W.top().second;
		float w = std::min(res.size.height, res.size.width);
		area += cv::contourArea(contours[W.top().first], false);
		width += w;
		W.pop();
	}
	return std::make_pair(std::make_pair(height / (size - 2 * pop_size), width / (size - 2 * pop_size)), area / (2 * size - 4 * pop_size));
}

// 寻找外接矩形
void plantInfo::findRect() {
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
	double font_scale=1;
	if (std::min(roi.rows, roi.cols) < 20)
		font_scale = 0.6;


	if (local + roi.rows < final_pic.rows) {
		if (flag == 0) {
			roi_img = (final_pic(cv::Range(local, local + roi.rows), cv::Range(0 + offset, offset + roi.cols)));
			putText(final_pic, "ID:" + std::to_string(ID), cv::Point(static_cast<int>(offset + avgHeight), (local + roi.rows - 5)), 2, font_scale, cv::Scalar(0, 0, 255), 1);
			local += roi.rows;
		}
		else {
			roi_img = (final_pic(cv::Range(local, local + roi.rows), cv::Range(0 + offset, offset + roi.cols)));
			putText(final_pic, "ID:" + std::to_string(ID), cv::Point(static_cast<int>(offset + avgHeight + 30), (local + roi.rows - 5)), 2, font_scale, cv::Scalar(0, 0, 255), 1);
			local += roi.rows;
		}
	}
	else {
		if (flag == 0) {
			bottom_Y = local;
			roi_img = (final_pic(cv::Range(new_line, new_line + roi.rows), cv::Range(offset + 300, offset + 300 + roi.cols)));
			putText(final_pic, "ID:" + std::to_string(ID), cv::Point(static_cast<int>(offset + 300 + avgHeight), (roi.rows + new_line)), 2, font_scale, cv::Scalar(0, 0, 255), 1);
			new_line += roi.rows;
		}
		else {
			bottom_Y = local;
			roi_img = (final_pic(cv::Range(new_line, new_line + roi.rows), cv::Range(offset + 300, offset + 300 + roi.cols)));
			putText(final_pic, "ID:" + std::to_string(ID), cv::Point(static_cast<int>(offset + 300 + avgHeight + 30), (roi.rows + new_line)), 2, font_scale, cv::Scalar(0, 0, 255), 1);
			new_line += roi.rows;
		}
	}
	roi.copyTo(roi_img);
}

// 书写最终长度
void plantInfo::putLength(std::string name, float Length, cv::Mat &final_pic) {

	if (new_line > 20)
		top_X = offset + 650;
	else
		top_X = offset + 400;
	// 上基准线
	cv::line(final_pic, cv::Point(top_X, top_Y), cv::Point(top_X + 100, top_Y), cv::Scalar(0, 0, 255), 5);

	// 下基准线
	bottom_X = top_X;
	bottom_Y = (bottom_Y == 0) ? local : bottom_Y;
	line(final_pic, cv::Point(bottom_X, bottom_Y), cv::Point(bottom_X + 100, bottom_Y), cv::Scalar(0, 0, 255), 5);

	// 中心线上半段
	// x坐标
	int semit_cenX = top_X + 50;
	// y坐标开始位置
	int semit_cenY = top_Y;
	// y坐标结束位置
	int y_end = static_cast<int>((top_Y + bottom_Y) / 2);
	cv::line(final_pic, cv::Point(semit_cenX, semit_cenY), cv::Point(semit_cenX, y_end - 20), cv::Scalar(0, 0, 255), 3);

	// 中心线下半段

	cv::line(final_pic, cv::Point(semit_cenX, y_end + 20), cv::Point(semit_cenX, bottom_Y), cv::Scalar(0, 0, 255), 3);
	char buffer[50];
	sprintf_s(buffer, "%0.2f", Length);

	// 书写总长度
	cv::putText(final_pic, name + buffer + "mm", cv::Point(semit_cenX - 100, y_end + 15), 2, 1, cv::Scalar(0, 0, 255), 2);

	bottom_Y = 0;
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
	cv::Mat &final_pic) {
	// 初始化顶格后新的行
	new_line = 20;
	top_Y = new_line;
//	std::ofstream Outfile("test.txt");
	
	int totalNum = seedNum < contours.size() ? seedNum : contours.size();
	for (int i = 0; i < totalNum; i++) {
		// 拷贝一份新图
		cv::Mat dst1 = dstH.clone();

		if (myqueH.empty())
			break;

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

		// 根据种子大小不同，使用不同得比例
		double weightRatio = 0;
		if (avgWidth > 50)
			weightRatio = 1.5;
		else
			weightRatio = 3;

		if (abs(height - avgHeight) > avgHeight / 3 || abs(width - avgWidth) > avgWidth / weightRatio ) {
			i--;
			continue;
		}
		
		// 根据凸包与周长之比
		convexHull(contours[ConNum], hull[ConNum], false);
		double convexLength = cv::arcLength(hull[ConNum], true);
		
		double contoursLength = cv::arcLength(contours[ConNum], true);
		if (convexLength / contoursLength < 0.95) {
			i--;
			continue;
		}

//		std::cout << convexLength / contoursLength << std::endl;
		// 针对小种子
		if (width < 20) {
			if (cv::contourArea(contours[ConNum]) < avgArea - 50) {
				i--;
				continue;
			}
		}


		// 确定真实的ID坐标
		int real_ID = -1;
		int min_dist = INT_MAX;

	//	cv::circle(final_pic, cv::Point(static_cast<int>(res.center.x), static_cast<int>(res.center.y)), 2, cv::Scalar(255, 0, 0), 8);
		for (size_t i = 0; i < 2000; i++) {
			if (seed_global[i].sWide == 0 && seed_global[i].sLength == 0)
				break;
			int real_x = seed_global[i].centerPt.x;
			int real_y = seed_global[i].centerPt.y;

			if (abs(real_x - static_cast<int>(res.center.x + offset_seed)) + abs(real_y - static_cast<int>(res.center.y)) < min_dist) {
				min_dist = abs(real_x - static_cast<int>(res.center.x + offset_seed)) + abs(real_y - static_cast<int>(res.center.y));
				real_ID = seed_global[i].ID;
			}
		}

		if (real_ID != -1) {
		//	cv::circle(final_pic, seed_global[real_ID].centerPt, 2, cv::Scalar(0, 0, 255), 8);
			totalHeight += std::max(seed_global[real_ID].sLength, seed_global[real_ID].sWide);
		}
		else
			totalHeight += 0;
		// 旋转图像
		// 定义旋转矩阵
		cv::Mat rot_mat;
		float angle = 0;

		// 测试分割开旋转，截取
		cv::Mat mask, seg_mat, seg_final;
		// 包含种子得外接矩形
//		std::cout << cv::Rect(res.boundingRect().tl(), res.boundingRect().br()) << std::endl;

		mask = dst1(cv::Rect(res.boundingRect().tl(), res.boundingRect().br()));
		// 切割图
		seg_mat = mask.clone();

		// 将种子平移到左上角
		int off_x = res.boundingRect().tl().x;
		int off_y = res.boundingRect().tl().y;

		for (int i = 0; i < contours[ConNum].size(); i++) {
			contours[ConNum][i].x -= off_x;
			contours[ConNum][i].y -= off_y;
		}
		flag[ConNum] = 1;

		// 将mask进行填充，种子区域为白色
		drawContours(mask, contours, ConNum, cv::Scalar(255, 255, 255), -1);
		// 转为灰度图
		cvtColor(mask, mask, CV_RGB2GRAY);
		// 二值化后使之变为外黑内白
		threshold(mask, mask, 254, 255, cv::THRESH_BINARY);
		// 取反，使之成为外白内黑
		cv::Mat mask1 = ~mask;
		// 背景需要灰色，所以建立一张灰色图
		//	cv::Mat gray(cv::Size(mask.cols, mask.rows), CV_8UC1, cv::Scalar(125));
		// 灰色图与外白内黑相与，就变成外灰内黑图
		//	gray &= mask1;

		// 因为要和三通道相与所以转为三通道图
		cvtColor(mask, mask, CV_GRAY2RGB);
		cvtColor(mask1, mask1, CV_GRAY2RGB);
		// 切割出种子得形状
		seg_mat.copyTo(seg_final, mask);
		// 将外灰内黑图与种子图相加，种子图为外黑内种子
		seg_final += mask1;


		int border = 70;
		copyMakeBorder(seg_final, seg_final, border, border, border, border, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));


		// 得到旋转矩阵和旋转角度
		cv::Point2f center;
		center.x = res.center.x - off_x + border;
		center.y = res.center.y - off_y + border;



		// 根据新的外接矩形计算旋转角度

		int ture_angle = 0;
		cv::RotatedRect true_rect;
		// 存储计算旋转矩阵得contours
		if (real_ID != -1) {
			// 计算旋转角度用图
			
			std::vector<std::vector<cv::Point>> contours_angle;

			cv::Point root_points[1][4];
			root_points[0][0] = seed_global[real_ID].pt1;
			root_points[0][1] = seed_global[real_ID].pt2;
			root_points[0][2] = seed_global[real_ID].pt3;
			root_points[0][3] = seed_global[real_ID].pt4;

			/*for (int i = 0; i < 4; i++) {
				cv::putText(dstH, std::to_string(i), P[i], 2, 1, cv::Scalar(0, 0, 255), 2);
				cv::line(dstH, P[i], P[(i + 1) % 4], cv::Scalar(0, 255, 0), 3);
			}


			for (int i = 0; i < 4; i++) {
				cv::putText(dstH, std::to_string(i), root_points[0][i], 2, 1, cv::Scalar(255, 0, 255), 2);
				cv::line(dstH, root_points[0][i], root_points[0][(i + 1) % 4], cv::Scalar(255, 0, 0),5);
			}*/


			cv::Mat temp(cv::Size(final_pic.cols, final_pic.rows), CV_8U, cv::Scalar(0));


			const cv::Point* ppt[1] = { root_points[0] };
			int npt[] = { 4 };
			cv::fillPoly(temp, ppt, npt, 1, cv::Scalar(255));

			


			cv::findContours(temp, contours_angle, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
			for (int i = 0; i < contours_angle.size(); i++) {
				true_rect = cv::minAreaRect(contours_angle[i]);

			//	ture_angle = true_rect.angle;
			}
		}


		

		
		
		
	//	std::cout << P[0] << " " << P[1] << " " << P[2] << " " << P[3] << std::endl;
	//	std::cout << seed_global[real_ID].pt1 << " " << seed_global[real_ID].pt2 << " " << seed_global[real_ID].pt3 << " " << seed_global[real_ID].pt4 << std::endl;


		float H = std::max(cv::minAreaRect(contours[ConNum]).size.height, cv::minAreaRect(contours[ConNum]).size.width);
		float W = std::min(cv::minAreaRect(contours[ConNum]).size.height, cv::minAreaRect(contours[ConNum]).size.width);
		
		// std::cout << "The ID:"<<real_ID<<" "<< H / W << std::endl;
	
		if (H / W < 2.5) {
			P[0].x = seed_global[real_ID].pt1.x - segloc > 0 ? seed_global[real_ID].pt1.x - segloc : seed_global[real_ID].pt1.x;
			P[0].y = seed_global[real_ID].pt1.y;
			P[2].x = seed_global[real_ID].pt3.x - segloc > 0 ? seed_global[real_ID].pt3.x - segloc : seed_global[real_ID].pt3.x;
			P[2].y = seed_global[real_ID].pt3.y;

			get_rotMat(true_rect, rot_mat, center, angle, 0);
		}
		else{
			get_rotMat(res, rot_mat, center, angle, 0);
		}

//		Outfile << "local angle: " << res.angle << std::endl;
//		Outfile << "real angele: " << ture_angle << std::endl;
		P[0].x -= (off_x - border);
		P[0].y -= (off_y - border);
		P[2].x -= (off_x - border);
		P[2].y -= (off_y - border);
		std::pair<cv::Point2f, cv::Point2f> Q_t = caclAngle(angle, P, center);

		cv::Mat test_rot;
		warpAffine(seg_final, test_rot, rot_mat, seg_final.size());
		cv::Mat final_test;
		final_test = test_rot(cv::Rect(Q_t.first, Q_t.second));
	//	std::cout << final_test.size() << std::endl;
		putROI(final_test, final_pic, 0, real_ID + 1);
	}
//	cv::imwrite("testH.jpg", dstH);
//	Outfile.close();
	putLength("H:", totalHeight, final_pic);
	offset = final_pic.cols / 2 + offsetw;
}


// 按照宽进行排序
void plantInfo::displayWidth(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW>& myqueW, cv::Mat &dstW,
	cv::Mat &final_pic) {

	int totalNum = seedNum < contours.size() ? seedNum : contours.size();
	// 重置记录长度，判断是否顶格，使之从0开始
	local = 20;



	// 记录标定线的Y值
	top_Y = local;
	// 初始化顶格后的长度
	new_line = 20;
	for (int i = 0; i < totalNum; i++) {
		cv::Mat dst1 = dstW.clone();
		if (myqueW.empty())
			break;

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

		double weightRatio = 0;
		if (avgWidth > 50)
			weightRatio = 1.5;
		else
			weightRatio = 3;

		

		if (abs(height - avgHeight) > avgHeight / 3 || abs(width - avgWidth) > avgWidth / weightRatio) {
			i--;
			continue;
		}

		// 根据凸包与周长之比
		convexHull(contours[ConNum], hull[ConNum], false);
		double convexLength = cv::arcLength(hull[ConNum], true);

		double contoursLength = arcLength(contours[ConNum], true);
		if (convexLength / contoursLength < 0.95) {
			i--;
			continue;
		}

		if (width < 20) {
			if (cv::contourArea(contours[ConNum]) < avgArea - 50) {
				i--;
				continue;
			}
		}


	//	cv::circle(final_pic, cv::Point(static_cast<int>(res.center.x), static_cast<int>(res.center.y)), 2, cv::Scalar(255, 0, 0), 8);
		// 确定真实的ID坐标
		// 确定真实的ID坐标
		int real_ID = -1;
		int min_dist = INT_MAX;
		for (size_t i = 0; i < 2000; i++) {
			if (seed_global[i].sWide == 0 && seed_global[i].sLength == 0)
				break;

			int real_x = seed_global[i].centerPt.x;
			int real_y = seed_global[i].centerPt.y;
			if (abs(real_x - static_cast<int>(res.center.x + offset_seed)) + abs(real_y - static_cast<int>(res.center.y)) < min_dist) {
				min_dist = abs(real_x - static_cast<int>(res.center.x + offset_seed)) + abs(real_y - static_cast<int>(res.center.y));
				real_ID = seed_global[i].ID;
			}
		}

		if (real_ID != -1) {
		//	cv::circle(final_pic, seed_global[real_ID].centerPt, 2, cv::Scalar(0, 0, 255), 8);

			totalWidth += std::min(seed_global[real_ID].sLength, seed_global[real_ID].sWide);
		}
		else {
			totalWidth += 0;
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


		// 将mask进行填充，种子区域为白色
		drawContours(mask, contours, ConNum, cv::Scalar(255, 255, 255), -1);
		// 转为灰度图
		cvtColor(mask, mask, CV_RGB2GRAY);
		// 二值化后使之变为外黑内白
		threshold(mask, mask, 254, 255, cv::THRESH_BINARY);
		// 取反，使之成为外白内黑
		cv::Mat mask1 = ~mask;
		// 背景需要灰色，所以建立一张灰色图
		//cv::Mat gray(cv::Size(mask.cols, mask.rows), CV_8UC1, cv::Scalar(125));
		// 灰色图与外白内黑相与，就变成外灰内黑图
		//gray &= mask1;

		// 因为要和三通道相与所以转为三通道图
		cvtColor(mask, mask, CV_GRAY2RGB);
		cvtColor(mask1, mask1, CV_GRAY2RGB);
		// 切割出种子得形状
		seg_mat.copyTo(seg_final, mask);
		// 将外灰内黑图与种子图相加，种子图为外黑内种子
		seg_final += mask1;

		int border = 70;
		copyMakeBorder(seg_final, seg_final, border, border, border, border, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));


		// 得到旋转矩阵和旋转角度
		cv::Point2f center;
		center.x = res.center.x - off_x + border;
		center.y = res.center.y - off_y + border;

		// 根据新的外接矩形计算旋转角度

		
		cv::RotatedRect true_rect;
		// 存储计算旋转矩阵得contours
		if (real_ID != -1) {

			// 计算旋转角度用图
			cv::Mat temp(cv::Size(final_pic.cols, final_pic.rows), CV_8UC1, cv::Scalar(0));
			std::vector<std::vector<cv::Point>> contours_angle;

			cv::Point root_points[1][4];
			root_points[0][0] = seed_global[real_ID].pt1;
			root_points[0][1] = seed_global[real_ID].pt2;
			root_points[0][2] = seed_global[real_ID].pt3;
			root_points[0][3] = seed_global[real_ID].pt4;
			const cv::Point* ppt[1] = { root_points[0] };
			int npt[] = { 4 };
			cv::fillPoly(temp, ppt, npt, 1, cv::Scalar(255));
			cv::findContours(temp, contours_angle, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
			for (int i = 0; i < contours_angle.size(); i++) {
				true_rect = cv::minAreaRect(contours_angle[i]);
				// angle = true_rect.angle;
			}
		}
		
	

	//	std::cout << P[0] << " " << P[1] << " " << P[2] << " " << P[3] << std::endl;
	//	std::cout << seed_global[real_ID].pt1 << " " << seed_global[real_ID].pt2 << " " << seed_global[real_ID].pt3 << " " << seed_global[real_ID].pt4 << std::endl;
		float H = std::max(cv::minAreaRect(contours[ConNum]).size.height, cv::minAreaRect(contours[ConNum]).size.width);
		float W = std::min(cv::minAreaRect(contours[ConNum]).size.height, cv::minAreaRect(contours[ConNum]).size.width);

		// std::cout << "The ID:" << real_ID << " " << H / W << std::endl;

		if (H / W < 2.5) {
			P[0].x = seed_global[real_ID].pt1.x - segloc > 0 ? seed_global[real_ID].pt1.x - segloc : seed_global[real_ID].pt1.x;
			P[0].y = seed_global[real_ID].pt1.y;
			P[2].x = seed_global[real_ID].pt3.x - segloc > 0 ? seed_global[real_ID].pt3.x - segloc : seed_global[real_ID].pt3.x;
			P[2].y = seed_global[real_ID].pt3.y;

			get_rotMat(true_rect, rot_mat, center, angle, 1);
		}
		else {
			get_rotMat(res, rot_mat, center, angle, 1);
		}



	//	get_rotMat(res, rot_mat, center, angle, 1);
		P[0].x -= (off_x - border);
		P[0].y -= (off_y - border);
		P[2].x -= (off_x - border);
		P[2].y -= (off_y - border);
		std::pair<cv::Point2f, cv::Point2f> Q_t = caclAngle(angle, P, center);

		cv::Mat test_rot;
		warpAffine(seg_final, test_rot, rot_mat, seg_final.size());
		cv::Mat final_test;
		final_test = test_rot(cv::Rect(Q_t.first, Q_t.second));
		putROI(final_test, final_pic, 1, real_ID + 1);
	}
	// cv::imwrite("testW.jpg", temp);
	putLength("W:", totalWidth, final_pic);
	offset = 20;
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

	cv::findContours(gray, contours, heierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	hull = std::vector<std::vector<cv::Point>>(contours.size());
	// 寻找外轮廓
	// 寻找外接矩形
	findRect();
	// 获得平均的高和宽
	std::pair<std::pair<float, float>, float> avg = caculateAvg(myqueH, myqueW);
	avgHeight = avg.first.first;
	avgWidth = avg.first.second;
	avgArea = avg.second;
	flag = std::vector<bool>(contours.size(), false);
	displayHeight(myqueH, semi_dst, final_pic);
	displayWidth(myqueW, semi_dst, final_pic);
}



