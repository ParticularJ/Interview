// SeedSizeDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include"API_SeedSize.h"

#define PI 3.14

// ��¼��
std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH> myqueH;
// ��¼��
std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW> myqueW;
// ��¼��û�д������ͼ
std::vector<bool> flag;


// ��¼����
std::vector<std::vector<cv::Point>> contours;

// ��¼heierarchy
std::vector<cv::Vec4i> heierarchy;

// ��¼͹��
std::vector<std::vector<cv::Point> > hull;

/*
parameters:
src: ��ֵͼ
dst: ԭͼ
final_pic: ���յĽ��ͼ
seedInfo: ������Ϣ�Ľṹ��
*/


plantInfo::plantInfo() {}

plantInfo::plantInfo(int seed) :seedNum(seed), totalHeight(0), totalWidth(0), top_X(0), top_Y(0), bottom_X(0), bottom_Y(0), offsetw(0), offseth(0), offset_seed(0) {}

plantInfo::~plantInfo() {}
int plantInfo::getImage(cv::Mat &src, cv::Mat &dst, cv::Mat &final_pic, SeedInfo* seedInfo) {
	final_pic = cv::Mat(cv::Size(3469, 2518), CV_8UC3, cv::Scalar(255, 255, 255));
	//	cv::imwrite("final.jpg", final_pic);
	// ��ն���
	while (!myqueH.empty()) {
		myqueH.pop();
	}
	while (!myqueW.empty()) {
		myqueW.pop();
	}


	// ��ʼ�����յĽ��ͼ
	// ��ʼ����¼����λ��
	plantInfo::local = 20;
	plantInfo::offset = 20;
	// ��ʼ���ṹ��ָ��
	plantInfo::seed_global = seedInfo;

	// ���ƽ���ĸߺͿ�
	avgHeight = 0;
	avgWidth = 0;
	avgArea = 0;
	offsetw = 0;
	offseth = 0;


	//���һ��ͼ
	cv::Rect rect_l, rect_r;
	rect_l = cv::Rect(0, 0, src.cols / 2, src.rows);
	rect_r = cv::Rect(src.cols / 2, 0, src.cols - src.cols / 2, src.rows);
	plantInfo::segloc = src.cols / 2;
	// ��ȡ�����ͼ
	cv::Mat img_L = src(rect_l);
	cv::Mat dst_L = dst(rect_l);



	SortSeed(img_L, dst_L, final_pic);


	// ��ն���
	while (!myqueH.empty()) {
		myqueH.pop();
	}
	while (!myqueW.empty()) {
		myqueW.pop();
	}

	// ���³�ʼ���ܸߺ��ܿ�
	totalWidth = 0;
	totalHeight = 0;
	offset_seed = segloc;

	plantInfo::local = 20;
	plantInfo::offsetw = 870;
	plantInfo::offseth = 870;
	plantInfo::offset += offseth;
	// ��ȡ�Ұ���ͼ
	cv::Mat img_R = src(rect_r);
	cv::Mat dst_R = dst(rect_r);
	SortSeed(img_R, dst_R, final_pic);
	return 1;
}

// ���ȶ��г��Ϳ�
/*
int : ��ǰ���ӵ�ID
rect: ���ӵ���Ϣ����ת�Ƕȣ���Ӿ��ε�
*/
void plantInfo::sort_record(std::pair<int, cv::RotatedRect> &rect) {
	myqueW.push(rect);
	myqueH.push(rect);
}


// ����ƽ���ĳ��Ϳ�
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

// Ѱ����Ӿ���
void plantInfo::findRect() {
	for (size_t i = 0; i < contours.size(); i++) {
		cv::RotatedRect rect = minAreaRect(contours[i]);
		// rect.boundingRect
		// �ֱ�ԸߺͿ��������
		sort_record(std::make_pair(static_cast<int>(i), rect));
	}
}


// ���������һ��ͼ��
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

// ��д���ճ���
void plantInfo::putLength(std::string name, float Length, cv::Mat &final_pic) {

	if (new_line > 20)
		top_X = offset + 650;
	else
		top_X = offset + 400;
	// �ϻ�׼��
	cv::line(final_pic, cv::Point(top_X, top_Y), cv::Point(top_X + 100, top_Y), cv::Scalar(0, 0, 255), 5);

	// �»�׼��
	bottom_X = top_X;
	bottom_Y = (bottom_Y == 0) ? local : bottom_Y;
	line(final_pic, cv::Point(bottom_X, bottom_Y), cv::Point(bottom_X + 100, bottom_Y), cv::Scalar(0, 0, 255), 5);

	// �������ϰ��
	// x����
	int semit_cenX = top_X + 50;
	// y���꿪ʼλ��
	int semit_cenY = top_Y;
	// y�������λ��
	int y_end = static_cast<int>((top_Y + bottom_Y) / 2);
	cv::line(final_pic, cv::Point(semit_cenX, semit_cenY), cv::Point(semit_cenX, y_end - 20), cv::Scalar(0, 0, 255), 3);

	// �������°��

	cv::line(final_pic, cv::Point(semit_cenX, y_end + 20), cv::Point(semit_cenX, bottom_Y), cv::Scalar(0, 0, 255), 3);
	char buffer[50];
	sprintf_s(buffer, "%0.2f", Length);

	// ��д�ܳ���
	cv::putText(final_pic, name + buffer + "mm", cv::Point(semit_cenX - 100, y_end + 15), 2, 1, cv::Scalar(0, 0, 255), 2);

	bottom_Y = 0;
}


// ������ת��ĵ�����
std::pair<cv::Point2f, cv::Point2f> plantInfo::caclAngle(float angle, cv::Point2f P[4], cv::Point2f &center) {
	// ������ת֮��P[0]��P[2]������
	cv::Point2f Q[2];
	float angle_arc = static_cast<float>(PI / 180.0 * angle);

	//  ��ĳ�����ĵ���ת��ʽ
	Q[0].x = (P[0].x - center.x)*cos(angle_arc) - (center.y - P[0].y)*sin(angle_arc) + center.x;
	Q[0].y = center.y - (P[0].x - center.x)*sin(angle_arc) - (center.y - P[0].y)*cos(angle_arc);
	Q[1].x = (P[2].x - center.x)*cos(angle_arc) - (center.y - P[2].y)*sin(angle_arc) + center.x;
	Q[1].y = center.y - (P[2].x - center.x)*sin(angle_arc) - (center.y - P[2].y)*cos(angle_arc);
	return std::make_pair(Q[0], Q[1]);
}

// �����ת����
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

// ���ո߽�������
void plantInfo::displayHeight(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH>& myqueH, cv::Mat &dstH,
	cv::Mat &final_pic) {
	// ��ʼ��������µ���
	new_line = 20;
	top_Y = new_line;
//	std::ofstream Outfile("test.txt");
	
	int totalNum = seedNum < contours.size() ? seedNum : contours.size();
	for (int i = 0; i < totalNum; i++) {
		// ����һ����ͼ
		cv::Mat dst1 = dstH.clone();

		if (myqueH.empty())
			break;

		//	ȡ����������
		std::pair<int, cv::RotatedRect> front = myqueH.top();

		cv::RotatedRect res = front.second;
		// ������λ������
		int ConNum = front.first;
		cv::Point2f P[4];
		res.points(P);
		myqueH.pop();

		const float height = std::max(res.size.height, res.size.width);
		const float width = std::min(res.size.height, res.size.width);

		// �������Ӵ�С��ͬ��ʹ�ò�ͬ�ñ���
		double weightRatio = 0;
		if (avgWidth > 50)
			weightRatio = 1.5;
		else
			weightRatio = 3;

		if (abs(height - avgHeight) > avgHeight / 3 || abs(width - avgWidth) > avgWidth / weightRatio ) {
			i--;
			continue;
		}
		
		// ����͹�����ܳ�֮��
		convexHull(contours[ConNum], hull[ConNum], false);
		double convexLength = cv::arcLength(hull[ConNum], true);
		
		double contoursLength = cv::arcLength(contours[ConNum], true);
		if (convexLength / contoursLength < 0.95) {
			i--;
			continue;
		}

//		std::cout << convexLength / contoursLength << std::endl;
		// ���С����
		if (width < 20) {
			if (cv::contourArea(contours[ConNum]) < avgArea - 50) {
				i--;
				continue;
			}
		}


		// ȷ����ʵ��ID����
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
		// ��תͼ��
		// ������ת����
		cv::Mat rot_mat;
		float angle = 0;

		// ���Էָ��ת����ȡ
		cv::Mat mask, seg_mat, seg_final;
		// �������ӵ���Ӿ���
//		std::cout << cv::Rect(res.boundingRect().tl(), res.boundingRect().br()) << std::endl;

		mask = dst1(cv::Rect(res.boundingRect().tl(), res.boundingRect().br()));
		// �и�ͼ
		seg_mat = mask.clone();

		// ������ƽ�Ƶ����Ͻ�
		int off_x = res.boundingRect().tl().x;
		int off_y = res.boundingRect().tl().y;

		for (int i = 0; i < contours[ConNum].size(); i++) {
			contours[ConNum][i].x -= off_x;
			contours[ConNum][i].y -= off_y;
		}
		flag[ConNum] = 1;

		// ��mask������䣬��������Ϊ��ɫ
		drawContours(mask, contours, ConNum, cv::Scalar(255, 255, 255), -1);
		// תΪ�Ҷ�ͼ
		cvtColor(mask, mask, CV_RGB2GRAY);
		// ��ֵ����ʹ֮��Ϊ����ڰ�
		threshold(mask, mask, 254, 255, cv::THRESH_BINARY);
		// ȡ����ʹ֮��Ϊ����ں�
		cv::Mat mask1 = ~mask;
		// ������Ҫ��ɫ�����Խ���һ�Ż�ɫͼ
		//	cv::Mat gray(cv::Size(mask.cols, mask.rows), CV_8UC1, cv::Scalar(125));
		// ��ɫͼ������ں����룬�ͱ������ں�ͼ
		//	gray &= mask1;

		// ��ΪҪ����ͨ����������תΪ��ͨ��ͼ
		cvtColor(mask, mask, CV_GRAY2RGB);
		cvtColor(mask1, mask1, CV_GRAY2RGB);
		// �и�����ӵ���״
		seg_mat.copyTo(seg_final, mask);
		// ������ں�ͼ������ͼ��ӣ�����ͼΪ���������
		seg_final += mask1;


		int border = 70;
		copyMakeBorder(seg_final, seg_final, border, border, border, border, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));


		// �õ���ת�������ת�Ƕ�
		cv::Point2f center;
		center.x = res.center.x - off_x + border;
		center.y = res.center.y - off_y + border;



		// �����µ���Ӿ��μ�����ת�Ƕ�

		int ture_angle = 0;
		cv::RotatedRect true_rect;
		// �洢������ת�����contours
		if (real_ID != -1) {
			// ������ת�Ƕ���ͼ
			
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


// ���տ��������
void plantInfo::displayWidth(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW>& myqueW, cv::Mat &dstW,
	cv::Mat &final_pic) {

	int totalNum = seedNum < contours.size() ? seedNum : contours.size();
	// ���ü�¼���ȣ��ж��Ƿ񶥸�ʹ֮��0��ʼ
	local = 20;



	// ��¼�궨�ߵ�Yֵ
	top_Y = local;
	// ��ʼ�������ĳ���
	new_line = 20;
	for (int i = 0; i < totalNum; i++) {
		cv::Mat dst1 = dstW.clone();
		if (myqueW.empty())
			break;

		// ��¼��Ϣ
		std::pair<int, cv::RotatedRect> front = myqueW.top();
		// ��ת������Ϣ
		cv::RotatedRect res = front.second;
		// contours ��Ϣ
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

		// ����͹�����ܳ�֮��
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
		// ȷ����ʵ��ID����
		// ȷ����ʵ��ID����
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


		// ��mask������䣬��������Ϊ��ɫ
		drawContours(mask, contours, ConNum, cv::Scalar(255, 255, 255), -1);
		// תΪ�Ҷ�ͼ
		cvtColor(mask, mask, CV_RGB2GRAY);
		// ��ֵ����ʹ֮��Ϊ����ڰ�
		threshold(mask, mask, 254, 255, cv::THRESH_BINARY);
		// ȡ����ʹ֮��Ϊ����ں�
		cv::Mat mask1 = ~mask;
		// ������Ҫ��ɫ�����Խ���һ�Ż�ɫͼ
		//cv::Mat gray(cv::Size(mask.cols, mask.rows), CV_8UC1, cv::Scalar(125));
		// ��ɫͼ������ں����룬�ͱ������ں�ͼ
		//gray &= mask1;

		// ��ΪҪ����ͨ����������תΪ��ͨ��ͼ
		cvtColor(mask, mask, CV_GRAY2RGB);
		cvtColor(mask1, mask1, CV_GRAY2RGB);
		// �и�����ӵ���״
		seg_mat.copyTo(seg_final, mask);
		// ������ں�ͼ������ͼ��ӣ�����ͼΪ���������
		seg_final += mask1;

		int border = 70;
		copyMakeBorder(seg_final, seg_final, border, border, border, border, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));


		// �õ���ת�������ת�Ƕ�
		cv::Point2f center;
		center.x = res.center.x - off_x + border;
		center.y = res.center.y - off_y + border;

		// �����µ���Ӿ��μ�����ת�Ƕ�

		
		cv::RotatedRect true_rect;
		// �洢������ת�����contours
		if (real_ID != -1) {

			// ������ת�Ƕ���ͼ
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


// �ֱ��ÿһ��ͼ�������������
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
	// Ѱ��������
	// Ѱ����Ӿ���
	findRect();
	// ���ƽ���ĸߺͿ�
	std::pair<std::pair<float, float>, float> avg = caculateAvg(myqueH, myqueW);
	avgHeight = avg.first.first;
	avgWidth = avg.first.second;
	avgArea = avg.second;
	flag = std::vector<bool>(contours.size(), false);
	displayHeight(myqueH, semi_dst, final_pic);
	displayWidth(myqueW, semi_dst, final_pic);
}



