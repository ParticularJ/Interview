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


/*
	parameters:
	src: ��ֵͼ
	dst: ԭͼ
	final_pic: ���յĽ��ͼ
	seedInfo: ������Ϣ�Ľṹ��
*/


plantInfo::plantInfo() {}

plantInfo::plantInfo(int seed) :seedNum(seed), totalHeight(0), totalWidth(0), top_X(0), top_Y(0), bottom_X(0), bottom_Y(0),offsetw(0), offseth(0) {}

plantInfo::~plantInfo() {}
int plantInfo::getImage(cv::Mat &src, cv::Mat &dst, cv::Mat &final_pic, SeedInfo* seedInfo) {
	final_pic = cv::Mat(cv::Size(dst.cols, dst.rows), CV_8UC3, cv::Scalar(0, 0, 0));
	// ��ʼ�����յĽ��ͼ
	// plantInfo::final_pic = cv::Mat(cv::Size(800, 600), CV_8UC3, cv::Scalar(0, 0, 0));
	// ��ʼ����¼����λ��
	plantInfo::local = 20;
	plantInfo::offset = 20;
	// ��ʼ���ṹ��ָ��
	plantInfo::seed_global = seedInfo;


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

// Ѱ����Ӿ���
void plantInfo::findRect(std::vector<std::vector<cv::Point>>& contours) {
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

	if (local + roi.rows < final_pic.rows) {
		if (flag == 0) {
			roi_img = (final_pic(cv::Range(local, local + roi.rows), cv::Range(0 + offset, offset + roi.cols)));
			putText(final_pic, "ID:" + std::to_string(ID), cv::Point(static_cast<int>(offset + avgHeight), (local + roi.rows - 5)), 2, 1, cv::Scalar(0, 0, 255), 1);
			local += roi.rows;
		}
		else {
			roi_img = (final_pic(cv::Range(local, local + roi.rows), cv::Range(0 + offset, offset + roi.cols)));
			putText(final_pic, "ID:" + std::to_string(ID), cv::Point(static_cast<int>(offset + avgHeight + 30), (local + roi.rows - 5)), 2, 1, cv::Scalar(0, 0, 255), 1);
			local += roi.rows;
		}
	}
	else {
		if (flag == 0) {
			bottom_Y = local;
			roi_img = (final_pic(cv::Range(new_line, new_line + roi.rows), cv::Range(offset + 300, offset + 300 + roi.cols)));
			putText(final_pic, "ID:" + std::to_string(ID), cv::Point(static_cast<int>(offset + 300 + avgHeight), (roi.rows + new_line)), 2, 1, cv::Scalar(0, 0, 255), 1);
			new_line += roi.rows;
		}
		else {
			bottom_Y = local;
			roi_img = (final_pic(cv::Range(new_line, new_line + roi.rows), cv::Range(offset + 300, offset + 300 + roi.cols)));
			putText(final_pic, "ID:" + std::to_string(ID) , cv::Point(static_cast<int>(offset + 300 + avgHeight + 30), (roi.rows + new_line)), 2, 1, cv::Scalar(0, 0, 255), 1);
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
								cv::Mat &final_pic, std::vector<std::vector<cv::Point>>& contours) {
	// ��ʼ��������µ���
	new_line = 20;
	top_Y = new_line;

	for (int i = 0; i < seedNum; i++) {
		// ����һ����ͼ
		cv::Mat dst1 = dstH.clone();
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


		if (abs(height - avgHeight) > avgHeight / 1.5 || abs(width - avgWidth) > avgWidth / 3) {
			i--;
			continue;
		}



		// ȷ����ʵ��ID����
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

		if (real_ID == -1) {
			totalHeight += 0;
		}
		else {
			totalHeight += std::max(seed_global[real_ID].sLength, seed_global[real_ID].sWide);
		}
		// ��תͼ��
		// ������ת����
		cv::Mat rot_mat;
		float angle = 0;

		// ���Էָ��ת����ȡ
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


		// �õ���ת�������ת�Ƕ�
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
	putLength("H:", totalHeight, final_pic);
	offset = dstH.cols + offsetw;
}


// ���տ��������
void plantInfo::displayWidth(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW>& myqueW, cv::Mat &dstW, 
									cv::Mat &final_pic, std::vector<std::vector<cv::Point>>& contours) {
	// ���ü�¼���ȣ��ж��Ƿ񶥸�ʹ֮��0��ʼ
	local = 20;

	// ��¼�궨�ߵ�Yֵ
	top_Y = local;
	// ��ʼ�������ĳ���
	new_line = 20;
	for (int i = 0; i < seedNum; i++) {
		cv::Mat dst1 = dstW.clone();
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

		if (abs(height - avgHeight) > avgHeight / 3 || abs(width - avgWidth) > avgWidth / 2) {
			i--;
			continue;
		}
		
		// ȷ����ʵ��ID����
		// ȷ����ʵ��ID����
		int real_ID = 0;
		for (size_t i = 0; i < contours.size(); i++) {
			int real_x = seed_global[i].centerPt.x > segloc ? seed_global[i].centerPt.x - segloc : seed_global[i].centerPt.x;
			int real_y = seed_global[i].centerPt.y;
			if (static_cast<int>(res.center.x) == real_x && static_cast<int>(res.center.y) == real_y) {
				real_ID = seed_global[i].ID;
				break;
			}
			else
				real_ID = 9999;
		}

		if (real_ID == -1) {
			totalWidth += 0;
		}
		else {
			totalHeight += std::min(seed_global[real_ID].sLength, seed_global[real_ID].sWide);
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


		// �õ���ת�������ת�Ƕ�
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
	// ��¼����
	std::vector<std::vector<cv::Point>> contours;

	// ��¼heierarchy
	std::vector<cv::Vec4i> heierarchy;

	cv::findContours(gray, contours, heierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	// Ѱ��������
	// Ѱ����Ӿ���
	findRect(contours);
	// ���ƽ���ĸߺͿ�
	std::pair<float, float> avg = caculateAvg(myqueH);
	avgHeight = avg.first;
	avgWidth = avg.second;
	flag = std::vector<bool>(contours.size(), false);
	displayHeight(myqueH, semi_dst, final_pic, contours);
	displayWidth(myqueW, semi_dst, final_pic, contours);
}


void plantInfo::simuStr(SeedInfo *seedInfo) {
	seedInfo[0].ID = 0;
	seedInfo[0].centerPt.x = 205;
	seedInfo[0].centerPt.y = 1714;
	seedInfo[0].sLength = 100;
	seedInfo[0].sWide = 50;

	seedInfo[1].ID = 1;
	seedInfo[1].centerPt.x = 738;
	seedInfo[1].centerPt.y = 1494;
	seedInfo[1].sLength = 100;
	seedInfo[1].sWide = 50;

	seedInfo[2].ID = 2;
	seedInfo[2].centerPt.x = 773;
	seedInfo[2].centerPt.y = 780;
	seedInfo[2].sLength = 100;
	seedInfo[2].sWide = 50;

	seedInfo[3].ID = 3;
	seedInfo[3].centerPt.x = 826;
	seedInfo[3].centerPt.y = 1252;
	seedInfo[3].sLength = 100;
	seedInfo[3].sWide = 50;
}



