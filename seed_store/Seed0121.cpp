#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<time.h>

using namespace std;
using namespace cv;

#define PI 3.14

RNG rng;

class cmpH {
public:
	bool operator() (const pair<int, RotatedRect> a, const pair<int, RotatedRect> b) {
		float maxa = a.second.size.width > a.second.size.height ? a.second.size.width : a.second.size.height;
		float maxb = b.second.size.width > b.second.size.height ? b.second.size.width : b.second.size.height;
		return maxa < maxb;
	}
};

class cmpW {
public:
	bool operator() (const pair<int, RotatedRect> a, const pair<int, RotatedRect> b) {
		float maxa = a.second.size.width < a.second.size.height ? a.second.size.width : a.second.size.height;
		float maxb = b.second.size.width < b.second.size.height ? b.second.size.width : b.second.size.height;
		return maxa < maxb;
	}
};



class plantInfo {
public:
	plantInfo() {}
	plantInfo(int seed):seedNum(seed), totalHeight(0), totalWidth(0), top_X(0), top_Y(0), bottom_X(0), bottom_Y(0){}
	~plantInfo() {}

private:
	// ��ʾͼƬ
	void display(Mat& src, string name) {
		namedWindow(name, WINDOW_NORMAL);
		imshow(name, src);
		waitKey(0);
	}

	// ��¼�ߡ���
	void sort_record(pair<int, RotatedRect> &rect) {
		myqueW.push(rect);
		myqueH.push(rect);
	}

	// ����ƽ���ߺͿ� �� ƽ�����
	// contΪ������������ͼ
	pair<pair<float, float>, float> caculateAvg(priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpH> H, 
													priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpW> W) {
	
		float height = 0;
		float width = 0;
		float area = 0;
		size_t size = H.size();
		int pop_size = static_cast<int>(contours.size() * 0.2);
		for (int i = 0; i < pop_size; i++) {
			H.pop();
			W.pop();
		}
		//����ƽ����
		while (H.size()-pop_size) {
			RotatedRect res = H.top().second;
			float h = max(res.size.height, res.size.width);
			area += contourArea(contours[H.top().first], false);
			height += h;
			H.pop();
		}
		while (W.size() - pop_size) {
			RotatedRect res = W.top().second;
			float w = min(res.size.height, res.size.width);
			area += contourArea(contours[W.top().first], false);
			width += w;
			W.pop();
		}
	//	cout << height<<" "<< size << " " << width << endl;
		return make_pair(make_pair(height / (size- 2*pop_size), width / (size- 2*pop_size)), area/(2*size-4*pop_size));
	}


	// Ѱ����Ӿ���
	void findRect(Mat &dst1) {
		record = vector<Mat>(contours.size(), Mat());
		for (size_t i = 0; i < contours.size(); i++) {
			RotatedRect rect = minAreaRect(contours[i]);

			Point2f P[4];
			rect.points(P);
			// ���Ƴ�����
			//for (int j = 0; j <= 3; j++)
			//{
			//	//	//cout << P[j];
			//	line(dst1, P[j], P[(j + 1) % 4], Scalar(255, 0, 255), 2);

			//}
			// rect.boundingRect
			// �ֱ�ԸߺͿ��������
			sort_record(make_pair(static_cast<int>(i), rect));
		}
	}

	// ���������ͬһ��ͼ��
	// flag 0 Ϊ����1Ϊ��
	void putROI(Mat &roi, int flag, int ID) {
		Mat roi_img;

		if (local + roi.rows < final_pic.rows) {
			if (flag == 0) {
				roi_img = (final_pic(Range(local, local + roi.rows), Range(0 + offset, offset + roi.cols)));
				putText(final_pic, "ID:" + to_string(ID), Point(offset + avgHeight, (local + roi.rows-5)), 2, 1, Scalar(0, 0, 255), 1);
				local += roi.rows;
			}
			else {
				roi_img = (final_pic(Range(local, local + roi.rows), Range(0 + offset, offset + roi.cols)));
				putText(final_pic, "ID:" + to_string(ID), Point(offset + avgHeight + 30, (local + roi.rows-5)), 2, 1, Scalar(0, 0, 255), 1);
				local += roi.rows;
			}
		}
		else { 
			if (flag == 0) {
				bottom_Y = local;
				roi_img = (final_pic(Range(new_line, new_line + roi.rows), Range(offset + 300, offset + 300 + roi.cols)));
				putText(final_pic, "ID:" + to_string(ID), Point(offset + 300 + avgHeight, (roi.rows + new_line)), 2, 1, Scalar(0, 0, 255), 1);
				new_line += roi.rows;
			}
			else {
				bottom_Y = local;
				roi_img = (final_pic(Range(new_line, new_line + roi.rows), Range(offset + 300 , offset + 300 + roi.cols)));
				putText(final_pic, "ID:" + to_string(ID), Point(offset + 300 + avgHeight + 30, (roi.rows + new_line)), 2, 1, Scalar(0, 0, 255), 1);
				new_line += roi.rows;
			}
		}
		roi.copyTo(roi_img);
		
		/*Mat test = final_pic.clone();
		resize(test, test, Size(800, 600));
		display(test, "final");*/
	}

	void putLength(string name, int Length) {

		if (new_line > 20) {
			top_X = offset + 650;
		}
		else {
			top_X = offset + 400;
		}
		// �ϻ�׼��
		line(final_pic, Point(top_X, top_Y), Point(top_X + 100, top_Y), Scalar(0, 0, 255), 5);
	
		// �»�׼��
		bottom_X = top_X;
		bottom_Y = (bottom_Y == 0) ? local : bottom_Y;
		line(final_pic, Point(bottom_X, bottom_Y), Point(bottom_X + 100, bottom_Y), Scalar(0, 0, 255), 5);

		// �������ϰ��
		// x����
		int semit_cenX = top_X + 50;
		// y���꿪ʼλ��
		int semit_cenY = top_Y;
		// y�������λ��
		int y_end = static_cast<int>((top_Y + bottom_Y) / 2);
		line(final_pic, Point(semit_cenX, semit_cenY), Point(semit_cenX, y_end-20), Scalar(0, 0, 255), 3);

		// �������°��

		line(final_pic, Point(semit_cenX, y_end+20), Point(semit_cenX, bottom_Y), Scalar(0, 0, 255), 3);
		
		// ��д�ܳ���
		putText(final_pic, name + to_string(Length) + "mm", Point(semit_cenX-100, y_end + 15), 2, 1, Scalar(0, 0, 255), 2);

		bottom_Y = 0;
	}


	//������ת�������
	pair<Point2f, Point2f> caclAngle(float angle, Point2f P[4], RotatedRect& res) {
		// ������ת֮��P[0]��P[2]������
		Point2f Q[2];
		float angle_arc = static_cast<float>(PI / 180.0 * angle);

		//  ��ĳ�����ĵ���ת��ʽ
		Q[0].x = (P[0].x - res.center.x)*cos(angle_arc) - (res.center.y - P[0].y)*sin(angle_arc) + res.center.x;
		Q[0].y = res.center.y - (P[0].x - res.center.x)*sin(angle_arc) - (res.center.y - P[0].y)*cos(angle_arc);
		Q[1].x = (P[2].x - res.center.x)*cos(angle_arc) - (res.center.y - P[2].y)*sin(angle_arc) + res.center.x;
		Q[1].y = res.center.y - (P[2].x - res.center.x)*sin(angle_arc) - (res.center.y - P[2].y)*cos(angle_arc);
		return make_pair(Q[0], Q[1]);
	}

	// test ��ת����
	pair<Point2f, Point2f> caclAngle(float angle, Point2f P[4], Point2f &center) {
		// ������ת֮��P[0]��P[2]������
		Point2f Q[2];
		float angle_arc = static_cast<float>(PI / 180.0 * angle);

		//  ��ĳ�����ĵ���ת��ʽ
		Q[0].x = (P[0].x - center.x)*cos(angle_arc) - (center.y - P[0].y)*sin(angle_arc) + center.x ;
		Q[0].y = center.y - (P[0].x - center.x)*sin(angle_arc) - (center.y - P[0].y)*cos(angle_arc) ;
		Q[1].x = (P[2].x - center.x)*cos(angle_arc) - (center.y - P[2].y)*sin(angle_arc) + center.x ;
		Q[1].y = center.y - (P[2].x - center.x)*sin(angle_arc) - (center.y - P[2].y)*cos(angle_arc) ;
		return make_pair(Q[0], Q[1]);
	}

	
	void get_rotMat(RotatedRect& res, Mat &rot_mat, float& angle, int flag) {
		if (flag == 0) {
		//	cout << "Height" << res.size.height << endl;
		//	cout << "Width" << res.size.width << endl;
			if (res.size.width > res.size.height) {
				if (res.angle != 0) {
					angle = 90 + res.angle;
					rot_mat = getRotationMatrix2D(res.center, angle, 1);
		//			cout << "trans angle:" << angle << endl;

				}
				else {
					angle = 90;
					rot_mat = getRotationMatrix2D(res.center, angle, 1);
		//			cout << "trans angle:" << angle << endl;
				}

			}
			else {
				if (res.angle != 0) {
					angle = res.angle;
					rot_mat = getRotationMatrix2D(res.center, angle, 1);
		//			cout << "trans angle:" << angle << endl;
				}
				else {
					rot_mat = getRotationMatrix2D(res.center, angle, 1);
				}
			}
		}
		else{
		//	cout << "Height" << res.size.height << endl;
		//	cout << "Width" << res.size.width << endl;
		//	cout << "The angle" << res.angle << endl;
			if (res.size.width < res.size.height) {
				if (res.angle != 0) {
					angle = (90 + res.angle);
					rot_mat = getRotationMatrix2D(res.center, angle, 1);
		//			cout << "trans angle:" << angle << endl;

				}
				else {
					angle = 90;
					rot_mat = getRotationMatrix2D(res.center, angle, 1);
		//			cout << "trans angle:" << angle << endl;
				}

			}
			else {
				if (res.angle != 0) {
					angle = res.angle;
					rot_mat = getRotationMatrix2D(res.center, angle, 1);
			//		cout << "trans angle:" << angle << endl;
				}
				else {
					angle = 0;
					rot_mat = getRotationMatrix2D(res.center, angle, 1);
				}
			}
		}
	}

	//  test �õ���ת�����Լ��Ƕ�

	void get_rotMat(RotatedRect& res, Mat &rot_mat, Point2f &center, float& angle, int flag) {
		if (flag == 0) {
			//	cout << "Height" << res.size.height << endl;
			//	cout << "Width" << res.size.width << endl;
			if (res.size.width > res.size.height) {
				if (res.angle != 0) {
					angle = 90 + res.angle;
					rot_mat = getRotationMatrix2D(center, angle, 1);
					//			cout << "trans angle:" << angle << endl;

				}
				else {
					angle = 90;
					rot_mat = getRotationMatrix2D(center, angle, 1);
					//			cout << "trans angle:" << angle << endl;
				}

			}
			else {
				if (res.angle != 0) {
					angle = res.angle;
					rot_mat = getRotationMatrix2D(center, angle, 1);
					//			cout << "trans angle:" << angle << endl;
				}
				else {
					rot_mat = getRotationMatrix2D(center, angle, 1);
				}
			}
		}
		else {
			//	cout << "Height" << res.size.height << endl;
			//	cout << "Width" << res.size.width << endl;
			//	cout << "The angle" << res.angle << endl;
			if (res.size.width < res.size.height) {
				if (res.angle != 0) {
					angle = (90 + res.angle);
					rot_mat = getRotationMatrix2D(center, angle, 1);
					//			cout << "trans angle:" << angle << endl;

				}
				else {
					angle = 90;
					rot_mat = getRotationMatrix2D(center, angle, 1);
					//			cout << "trans angle:" << angle << endl;
				}

			}
			else {
				if (res.angle != 0) {
					angle = res.angle;
					rot_mat = getRotationMatrix2D(center, angle, 1);
					//		cout << "trans angle:" << angle << endl;
				}
				else {
					angle = 0;
					rot_mat = getRotationMatrix2D(center, angle, 1);
				}
			}
		}
	}





	// չʾ��
	// dstΪ��Ӧ��ԭͼ
	void displayHeight(priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpH>& myqueH, Mat &dst) {
		// ��ʼ��������µ���
		new_line = 20;
		top_Y = new_line;
		for (int i = 0; i < seedNum; i++) {
		//	clock_t s2 = clock();
			// ����һ����ͼ
			Mat dst1 = dst.clone();
		//	display(dst1, "dst1");
			pair<int, RotatedRect> front = myqueH.top();
			//	ȡ����������
			RotatedRect res = front.second;
			// ������λ������
			int ConNum = front.first;
		//	cout << "The area:" << res.size.area() << endl;
			Point2f P[4];
			res.points(P);
			// ���Ƴ�����
			//for (int j = 0; j <= 3; j++)
			//{
			//	//	//cout << P[j];
			//	line(dst1, P[j], P[(j + 1) % 4], Scalar(255, 0, 255), 1);

			//}


			//cout << "The angle is:" << res.angle << endl;
			myqueH.pop();
			
			



			const float height = max(res.size.height, res.size.width);
			const float width = min(res.size.height, res.size.width);
		   // cout << height<<" "<< width<< endl;

			
			double weightRatio = 0;
			if (avgWidth > 50)
				weightRatio = 1.5;
			else
				weightRatio = 3;
			
			if (abs(height - avgHeight) > avgHeight/ 3 || abs(width - avgWidth) > avgWidth/ weightRatio) {
			//	cout << "error:" << height << " " << width << endl;
				// չʾ����ͼ��
				for (int j = 0; j <= 3; j++) {
					//	//	//cout << P[j];
					line(dst1, P[j], P[(j + 1) % 4], Scalar(0, 255, 0), 3);
				}
				// resize(dst1, dst1, Size(800, 600));
				display(dst1, "error1");
				i--;
				continue;
			}

			// ����͹�����ܳ�֮��
			
			convexHull(contours[ConNum], hull[ConNum], false);
			double convexLength = arcLength(hull[ConNum], true);
			double contoursLength = arcLength(contours[ConNum], true);
		//	cout << "͹������" << convexLength << " " << "�������� " << contoursLength << endl;

			if (convexLength / contoursLength < 0.92) {
				i--;
				continue;
			}
			

			if (width < 20) {
				cout << contourArea(contours[ConNum]) << endl;
				if (contourArea(contours[ConNum]) < avgArea - 50) {
					i--;
					continue;
				}
			}


			totalHeight += height;
			// ��תͼ��
			// ������ת����
			Mat rot_mat;
			float angle = 0;

			



			/*

			// ���Էָ��ת����ȡ
		//	clock_t s2 = clock();
			Mat mask, seg_mat, seg_final;
			// ���mask
			mask = dst1(Rect(res.boundingRect().tl(), res.boundingRect().br()));
			seg_mat = mask.clone();
			// ������ˣ�ʹ��ͼ�񶼴����Ͻǿ�ʼ
			int off_x = res.boundingRect().tl().x ;
			int off_y = res.boundingRect().tl().y ;
			
			// ����������ƫ����
			for (int i = 0; i < contours[ConNum].size(); i++) {
				contours[ConNum][i].x -= off_x;
				contours[ConNum][i].y -= off_y;
			}
			flag[ConNum] = 1;

			clock_t t = clock();
			// �����ķ�ʽ�����������γ�����maskͼ
			drawContours(mask, contours, ConNum, Scalar(255, 255, 255), -1);
			cvtColor(mask, mask, CV_RGB2GRAY);
			threshold(mask, mask, 254, 255, THRESH_BINARY);
			Mat mask1 = ~mask;
			Mat back(mask.rows, mask.cols, CV_8UC1, Scalar(125));
			mask1 &= back;
			

			clock_t e = clock();
			cout << e - t << "ms" << endl;
			// ��ֵͼתΪ��ͨ��ͼ
			// mask.convertTo(mask, CV_8UC3);
			cvtColor(mask, mask, CV_GRAY2RGB);
			cvtColor(mask1, mask1, CV_GRAY2RGB);
			cout << mask.channels() << " " << mask1.channels() << endl;

			display(mask, "mask");
			display(mask1, "mask1");
			
			// �����и�
			seg_mat.copyTo(seg_final, mask);
			display(seg_final, "mask");

			
			add(seg_final, mask1, seg_final);

 			// ���䣬��ֹ��תʱ��Խ��
			int border = 70;
			copyMakeBorder(seg_final, seg_final, border, border, border, border, BORDER_CONSTANT, Scalar(0, 0, 0));
			



			// �õ���ת�������ת�Ƕ�
			Point2f center;
			center.x = res.center.x - off_x + border;
			center.y = res.center.y - off_y + border;
			
			get_rotMat(res, rot_mat, center, angle, 0);
			P[0].x -= (off_x - border);
			P[0].y -= (off_y - border);
			P[2].x -= (off_x - border);
			P[2].y -= (off_y - border);
			pair<Point2f, Point2f> Q_t = caclAngle(angle, P, center);

		//	cout << "P1:"<<P[0] << " " << "Q1"<<Q_t.first << endl;
		//	cout << "P2:"<<P[2] << " " << "Q2"<<Q_t.second << endl;
			Mat test_rot;
		//	display(seg_final, "seg");
		//	cout << seg_final.size();
			warpAffine(seg_final, test_rot, rot_mat, seg_final.size());
		//	cout << test_rot.size();
			Mat final_test;
		    final_test = test_rot(Rect(Q_t.first, Q_t.second));
			cout << final_test.size();
			putROI(final_test, 0, 4);
			display(final_test, "test_rot");
		//	imshow("test", final_test);
		//	waitKey(0);
			//cout<<contours[ConNum].size();
		//	clock_t e2 = clock();
		//	cout << "contours time:" << e2 - s2 << "ms" << endl;
			
			*/


			
		//	cout << "area: " << contourArea(contours[ConNum], true) << endl;

			// �õ���ת�������ת�Ƕ�
			get_rotMat(res, rot_mat, angle, 0);
			
			// �õ�ROI��������ϽǺ����½ǵĵ�
			pair<Point2f, Point2f> Q = caclAngle(angle, P, res);

			// �޸Ĺ���ͼƬ
			drawCon(dst1, ConNum, res);
		//	display(dst1, "dst1");
			// �޸Ĺ���ͼ
			Mat dst2 = record[ConNum];
			//threshold(dst2, dst2, 244, 255, THRESH_BINARY);
			//Mat dst3;
			//dst2.convertTo(dst2, CV_8UC3);
		
			//dst.copyTo(dst3, dst2);
	
		//	display(dst3, "test1");
		//	display(dst2, "dst2");

			// ��ת֮���ͼ��
	
			Mat rot_image;
			warpAffine(dst2, rot_image, rot_mat, Size(dst2.size()));//ԭͼ����ת

			// �õ�ÿһ�����ӵ�ͼ
			Mat ROI = rot_image(Rect(Q.first, Q.second));

			//Point Center;
			//Center.x = static_cast<int>(res.center.x);
			//Center.y = static_cast<int>(res.center.y);
			//cout << "The No.: " << ConNum << " Center_X: " << Center.x << " Center_Y: " << Center.y << endl;
			//cout << "The Rows" << ROI.rows << "THe COls" << ROI.cols << endl;
//			if (ROI.rows <= 80 && ROI.cols <= 80) {
//				resize(ROI, ROI, Size(ROI.cols * 2, ROI.rows * 2));
//			}
			cout << ROI.size() << endl;
		//	display(ROI, "roi");
			// ���ܵ�һ��ͼ 
		    putROI(ROI, 0, ConNum);
			// ����ʹ֮Ϊ0 
			// display(ROI, "ROI");
			// ������Ӿ����Ƿ�ɹ�
			resize(dst2, dst2, Size(800, 600));
			display(dst2, "resH");

			
		}
		putLength("H:", totalHeight);
		offset = final_pic.cols / 2 + offsetw;
		//display(dst, "resH");
	}


	// չʾ��
	// dstΪԭ����һ��ͼ
	void displayWidth(priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpW>& myqueW, Mat &dst) {
		// ���ü�¼���ȣ��ж��Ƿ񶥸�ʹ֮��0��ʼ
		local = 20;

		// ��¼�궨�ߵ�Yֵ
		top_Y = local;
		// ��ʼ�������ĳ���
		new_line = 20;
		for (int i = 0; i < seedNum; i++) {
			Mat dst1 = dst.clone();
			// ��¼��Ϣ
			pair<int, RotatedRect> front = myqueW.top();
			// ��ת������Ϣ
			RotatedRect res = front.second;
			// contours ��Ϣ
			int ConNum = front.first;
			Point2f P[4];
			res.points(P);


		//	cout << "The angle is:" << res.angle << endl;
			// ������Ӿ���
			//for (int j = 0; j <= 3; j++){
			//	//	//cout << P[j];
			//	line(dst1, P[j], P[(j + 1) % 4], Scalar(0, 255, 0), 3);
			//}
			myqueW.pop();

			const float height = max(res.size.height, res.size.width);
			const float width = min(res.size.height, res.size.width);
		//	cout << height<<" "<< width<< endl;
			double weightRatio = 0;
			if (avgWidth > 50)
				weightRatio = 1.5;
			else
				weightRatio = 3;


			if (abs(height - avgHeight) > avgHeight / 3 || abs(width - avgWidth) > avgWidth / weightRatio) {
			//	cout<<"error:"<< height << " " << width << endl;
				// չʾ����ͼ��
				for (int j = 0; j <= 3; j++){
				//	//	//cout << P[j];
					line(dst1, P[j], P[(j + 1) % 4], Scalar(0, 255, 0), 3);
				}
			//	resize(dst1, dst1, Size(800, 600));
				display(dst1, "error2");
				i--;
				continue;
			}

			// ����͹�����ܳ�֮��

			convexHull(contours[ConNum], hull[ConNum], false);
			double convexLength = arcLength(hull[ConNum], true);
			double contoursLength = arcLength(contours[ConNum], true);
		//	cout << "͹������" << convexLength << " " << "�������� " << contoursLength << endl;

			if (convexLength / contoursLength < 0.92) {
				i--;
				continue;
			}

		

			if (width < 20) {
				cout << contourArea(contours[ConNum]) << endl;
				if (contourArea(contours[ConNum]) < avgArea - 50) {
					i--;
					continue;
				}
			}

			// �ܿ��
			totalWidth += width;

			// ��ת�������ת�Ƕ�
			Mat rot_mat;
			float angle = 0;

			
			
			//cout << "area: " << contourArea(contours[ConNum], true) << endl;
			/*
		//	clock_t s2 = clock();
			Mat mask, seg_mat, seg_final;
			mask = dst1(Rect(res.boundingRect().tl(), res.boundingRect().br()));
			//display(mask, "mask");
			seg_mat = mask.clone();
			int off_x = res.boundingRect().tl().x;
			int off_y = res.boundingRect().tl().y;

			if (!flag[ConNum]) {
				for (int i = 0; i < contours[ConNum].size(); i++) {
					contours[ConNum][i].x -= off_x;
					contours[ConNum][i].y -= off_y;
				}
			}


			drawContours(mask, contours, ConNum, Scalar(255, 255, 255), -1);

			cvtColor(mask, mask, CV_RGB2GRAY);
			threshold(mask, mask, 254, 255, THRESH_BINARY);
			
		//	display(mask, "thresh_mask");
			mask.convertTo(mask, CV_8UC3);
			seg_mat.copyTo(seg_final, mask);

			int border = 70;
			copyMakeBorder(seg_final, seg_final, border, border, border, border, BORDER_CONSTANT, Scalar(0, 0, 0));


			// �õ���ת�������ת�Ƕ�
			Point2f center;
			center.x = res.center.x - off_x + border;
			center.y = res.center.y - off_y + border;

			get_rotMat(res, rot_mat, center, angle, 1);
			P[0].x -= (off_x - border);
			P[0].y -= (off_y - border);
			P[2].x -= (off_x - border);
			P[2].y -= (off_y - border);
			pair<Point2f, Point2f> Q_t = caclAngle(angle, P, center);

		//	cout << "P1:" << P[0] << " " << "Q1" << Q_t.first << endl;
		//	cout << "P2:" << P[2] << " " << "Q2" << Q_t.second << endl;
			Mat test_rot;
		//	display(seg_final, "seg");
		//	cout << seg_final.size();
			warpAffine(seg_final, test_rot, rot_mat, seg_final.size());
		//	cout << test_rot.size();
			Mat final_test;
			final_test = test_rot(Rect(Q_t.first, Q_t.second));
			putROI(final_test, 1);
		//	display(test_rot, "test_rot");
		//	imshow("test", final_test);
		//	waitKey(0);
			//cout<<contours[ConNum].size();
		//	clock_t e2 = clock();
		//	cout << "contours time:" << e2 - s2 << "ms" << endl;

		*/

			


			


			// �õ���ת�������ת�Ƕ�
			get_rotMat(res, rot_mat, angle, 1);
			// ������ת֮��P[0]��P[2]������
			pair<Point2f, Point2f> Q = caclAngle(angle, P, res);

			// �޸Ĺ���ͼƬ
			drawCon(dst1, ConNum, res);

			
			Mat dst2 = record[ConNum];
		//	display(dst2, "dst2");
			//threshold(dst2, dst2, 244, 255, THRESH_BINARY);
			//dst2.convertTo(dst2, CV_8UC3);

			//Mat dst3;
			// display(dst2, "test2");
			//dst.copyTo(dst3, dst2);
		

			// ��ת֮���ͼ��
			Mat rot_image;
			warpAffine(dst2, rot_image, rot_mat, Size(dst2.size()));//ԭͼ����ת
																   // �õ�ÿһ�����ӵ�ͼ
			Mat ROI = rot_image(Rect(Q.first, Q.second));
			// cout << "The Rows" << ROI.rows << "THe COls" << ROI.cols << endl;
		//	Point Center;
		//	Center.x = static_cast<int>(res.center.x);
		//	Center.y = static_cast<int>(res.center.y);
		//	cout << "The No.: " << ConNum << " Center_X: " << Center.x << " Center_Y: " << Center.y << endl;
			
			
//			if (ROI.rows <= 80 && ROI.cols <= 80) {
//				resize(ROI, ROI, Size(ROI.cols * 2, ROI.rows * 2));
//			}

		//	display(ROI, "roi");


		

			// ���ܵ�һ��ͼ 
			putROI(ROI, 1, ConNum);
		
			// ������Ӿ����Ƿ�ɹ�
			resize(dst2, dst2, Size(800, 600));
			display(dst2, "resw");
			
		}
		putLength("W:", totalWidth);
		offset = 20;
	}
	
	// ����ǰ������ 
	// ConNum ��ǰ����������, ��ȥ���޹�����
	// dst Ϊ��Ҫȥ��������ͼ
	void drawCon(Mat &dst, int ConNum, RotatedRect &res) {
		Mat dst1 = dst.clone();
		// ��¼��ת��Ӿ���
		vector<Rect> boundingbox(1);
		boundingbox[0]=res.boundingRect();
		if (record[ConNum].empty()) {
			// drawContours(dst1, contours, ConNum, Scalar(255, 255, 255), -1);
			//	cout << boundingbox[0].tl().x << " " << boundingbox[0].tl().y << endl;
			//	cout << boundingbox[0].br().x << " " << boundingbox[0].br().y << endl;
			for (int i = boundingbox[0].tl().x; i < boundingbox[0].br().x; i++) {
				for (int j = boundingbox[0].tl().y; j < boundingbox[0].br().y; j++) {
					//	cout << "(" << i << "," << j << ")" << " ";
					if (pointPolygonTest(contours[ConNum], Point2i(i, j), false) == -1) {
						if (i < 0)
							i = 0;
						if (j < 0)
							j = 0;
						dst.at<Vec3b>(j, i)[0] = 125;
						dst.at<Vec3b>(j, i)[1] = 125;
						dst.at<Vec3b>(j, i)[2] = 125;
					}
				}
			}
			record[ConNum] = dst;
		}
	//	display(dst1, "Rec");
	//	for (int i = 0; i < contours[ConNum].size(); i++) {
	//		cout << contours[ConNum][i]<<" ";
	//	}
	//	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		// ��ת��Ӿ���
	//	rectangle(dst1, boundingbox[0].tl(), boundingbox[0].br(), color, 2);
	//	drawContours(dst1, contours, ConNum, color, 2, 8, heierarchy, 0, Point());
	//	display(dst1, "Contours");

	//	size_t e = clock();
		//cout << e - s << "ms" << endl;
	}

	// print Height 
	void printQue(priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpH>& myque) {
		while (!myque.empty()) {
			float h = myque.top().second.size.width;
			float w = myque.top().second.size.height;
			float res = h > w ? h : w;
			//cout << "resH"<< res << endl;
			myque.pop();
		}
	}

	// print Width
	void printQue(priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpW>& myque) {
		while (!myque.empty()) {
			float h = myque.top().second.size.width;
			float w = myque.top().second.size.height;
			float res = h < w ? h : w;
			//cout << "resW"<< res << endl;
			myque.pop();
		}
	}


private:
	// �����ӽ�������srcΪ��ֵͼ��������ң�
	// dstΪ��Ӧ��ԭͼ��������ң�
	void SortSeed(Mat &src, Mat &dst) {
		Mat gray;

		// convert to gray
		//cvtColor(src, gray, CV_RGB2GRAY);
		//GaussianBlur(src, gray, Size(3, 3), 0, 0);
		// convert to binary
		threshold(src, gray, 135, 255, THRESH_BINARY);
	    display(gray, "binary_pic");
		// RETR_EXTERNAL record outer
		// CHAIN_APPROX_SIMPLE record conor points
		findContours(gray, contours, heierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		hull = vector<vector<Point>>(contours.size());
		// Ѱ��������
		// drawCon(dst);
		// Ѱ����Ӿ���
		findRect(dst);
		//cout << myqueH.size();
		pair<pair<float, float>, float> avg = caculateAvg(myqueH, myqueW);
		avgHeight = avg.first.first;
		avgWidth = avg.first.second;
		avgArea = avg.second;
		//cout << myqueH.size();
	    cout << "avgHeight: "<<avgHeight << " avgWidth: " << avgWidth <<" avgArea: "<<avgArea<< endl;
		// ��ӡ��
		// printQue(myqueH);
		// չʾ��
		flag = vector<bool>(contours.size(), false);


		displayHeight(myqueH, dst);
		
	//	cout << endl;
	//	display(final_pic, "Height");
		//cout << endl;
		// printQue(myqueW);
		displayWidth(myqueW, dst);

		display(final_pic, "Weight");
		imwrite("D://Myself//Dataset//20190121//final//F52_10.jpg", final_pic);
	//	waitKey(0);
		
	}
public:	
	Mat& getImage(Mat &src, Mat& dst1) {
		// ��ʼ�����յĽ��ͼ
		final_pic = Mat(2518, 3469, CV_8UC3, Scalar(125,125,125));
		// ���ƽ���ĸߺͿ�
		avgHeight = 0;
		avgWidth = 0;
		avgArea = 0;
		offsetw = 0;
		offseth = 0;
		// ��ʼ����¼����λ��
		local = 20;
		offset = 20;
		//���һ��ͼ
		Rect rect_l, rect_r;
		rect_l = Rect(0, 0, src.cols/2, src.rows);
		rect_r = Rect(src.cols / 2, 0, src.cols-src.cols/2, src.rows);

		


		// ��ȡ�����ͼ
		Mat img_L = src(rect_l);
	//	cout << src.cols / 2 << " " << src.rows << endl;
	//	cout << dst1.rows << " " << dst1.cols << endl;
		dst_L = dst1(rect_l);
		
		SortSeed(img_L, dst_L);

	//	resize(dst_L, dst_L, Size(800, 600));
	//	display(dst_L, "left");

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


		// ������ֵר��
		record.clear();
	

		local = 20;
		offsetw = 870;
		offseth = 870;
		offset += offseth;
		// ��ȡ�Ұ���ͼ
		Mat img_R = src(rect_r);
		dst_R = dst1(rect_r);
		SortSeed(img_R, dst_R);
	//	resize(dst_R, dst_R, Size(800, 600));
	//	display(dst_R, "right");
	//	resize(final_pic, final_pic, Size(800, 600));
		display(final_pic, "final");
		
	//	imwrite("C:/Myself/Dataset/result/F24.jpg", final_pic);
		return final_pic;
	}


private:
	// ��¼ƽ���ĳ��Ϳ�
	double avgHeight, avgWidth, avgArea;
	// local ��ʾÿ�����Ӵﵽ��ײ�Խ��ʱ���޸Ĳ���
	// offset ��ʾ�ұ����ӵ�ƫ����
	int local, offset, offsetw, offseth;
	// ��¼ԭͼ, ��ԭͼ����ԭͼ
	Mat DST, dst_L, dst_R;
	// ÿ�γ����㹻������һ�п�ʼ
	int new_line;
	
	// ͳ�����ӵĸ���
	int seedNum;
	// ���ճ��Ż��ǿ���
	bool byHeightOrWidth;

	// ��¼�ܳ��ȣ��Լ��ܿ��
	int totalHeight;
	int totalWidth;
	// ��¼���»�׼��λ��
	int top_X;
	int top_Y;
	int bottom_X;
	int bottom_Y;



	// ��¼�����Ƿ񱻴����
	vector<Mat> record;

	// ��¼��û�д������ͼ
	vector<bool> flag;
	
	// ��¼͹��
	vector<vector<Point>> hull;
	// ��¼����
	vector<vector<Point>> contours;
	// ������ͼ
	Mat final_pic;
	// ��¼heierarchy
	vector<Vec4i> heierarchy;
	// ��¼��
	priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpH> myqueH;
	// ��¼��
	priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpW> myqueW;
};

int main() {
	size_t start = clock();
	// Input Image
	Mat src, dst;
	// ˮ��
//	dst = imread("a1_src1.jpg");
//	src = imread("1.jpg");
	// ����	
//	dst = imread("a1_src0.jpg");
//	src = imread("2.jpg");

	// ����ͼƬ��
	src = imread("D://Myself//Dataset//20190121//wheat//E52.jpg", 0);
	dst = imread("D://Myself//Dataset//20190121//20190121//D52.jpg");
//	resize(src, src, Size(src.cols / 2, src.rows / 2));
//	resize(dst, dst, Size(dst.cols / 2, dst.rows / 2));
	// exceptional 
	if (src.empty()||dst.empty()) {
		cerr << "No image!";
		return -1;
	}
	// init object
	plantInfo seed(20);

	// display
	// pod.display(src, "ori");
	Mat final_test = seed.getImage(src, dst);
	imshow("final", final_test);
	waitKey(0);
	size_t end = clock();
	cout << end - start << "ms" << endl;
	return 0;
}