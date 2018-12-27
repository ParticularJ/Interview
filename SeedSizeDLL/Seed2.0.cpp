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

	// ����ƽ���ߺͿ�
	pair<float, float> caculateAvg(priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpH> H) {
	
		float height = 0;
		float width = 0;
		size_t size = H.size();
		for (int i = 0; i < 3; i++) {
			H.pop();
		}
		while (!H.empty()) {
			RotatedRect res = H.top().second;
			float h = max(res.size.height, res.size.width);
			float w = min(res.size.height, res.size.width);
			height += h;
			width += w;
			H.pop();
		}
	
	//	cout << height<<" "<< size << " " << width << endl;
		return make_pair(height / (size-3), width / (size-3));
	}


	// Ѱ����Ӿ���
	void findRect() {
		record = vector<Mat>(contours.size(), Mat());
		for (int i = 0; i < contours.size(); i++) {
			RotatedRect rect = minAreaRect(contours[i]);
			// rect.boundingRect
			// �ֱ�ԸߺͿ��������
			sort_record(make_pair(i, rect));
		}
	}

	// ���������ͬһ��ͼ��
	// flag 0 Ϊ����1Ϊ��
	void putROI(Mat &roi, int flag) {
		Mat roi_img;

		if (local + roi.rows < final_pic.rows) {
			if(flag == 0)
				roi_img = (final_pic(Range(local, local + roi.rows), Range(0 + offset, offset + roi.cols)));
			else {
				roi_img = (final_pic(Range(local, local + roi.rows), Range(offset + static_cast<int>(avgHeight) * 2 + static_cast<int>(avgWidth), offset + static_cast<int>(avgHeight) * 2 + static_cast<int>(avgWidth) + roi.cols)));
			}
		}
		else {
			if (flag == 0) {
				roi_img = (final_pic(Range(new_line, roi.rows + new_line), Range(offset + static_cast<int>(avgHeight), offset + static_cast<int>(avgHeight) + roi.cols)));
				new_line += roi.rows;
			}
			else {
				roi_img = (final_pic(Range(new_line, roi.rows + new_line), Range(offset + static_cast<int>(avgHeight) * 3 + static_cast<int>(avgWidth), offset + static_cast<int>(avgHeight) * 3 + static_cast<int>(avgWidth) + roi.cols)));
				new_line += roi.rows;
			}
		}
		roi.copyTo(roi_img);
		local += roi.rows;
		/*Mat test = final_pic.clone();
		resize(test, test, Size(800, 600));
		display(test, "final");*/
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
		new_line = 0;
		
		for (int i = 0; i < 20; i++) {
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


			if (abs(height - avgHeight) > avgHeight/ 3 || abs(width - avgWidth) > avgWidth/ 2) {
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
			// ��תͼ��
			// ������ת����
			Mat rot_mat;
			float angle = 0;



			
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
			clock_t e = clock();
			cout << e - t << "ms" << endl;
			// ��ֵͼתΪ��ͨ��ͼ
			mask.convertTo(mask, CV_8UC3);
			// �����и�
			seg_mat.copyTo(seg_final, mask);
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
			putROI(final_test, 0);
			display(test_rot, "test_rot");
		//	imshow("test", final_test);
		//	waitKey(0);
			//cout<<contours[ConNum].size();
		//	clock_t e2 = clock();
		//	cout << "contours time:" << e2 - s2 << "ms" << endl;
			



			/*

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


			// ��ת֮���ͼ��
	
			Mat rot_image;
			warpAffine(dst2, rot_image, rot_mat, Size(dst2.size()));//ԭͼ����ת

			// �õ�ÿһ�����ӵ�ͼ
			Mat ROI = rot_image(Rect(Q.first, Q.second));
			
			// ���ܵ�һ��ͼ 
			// putROI(ROI, 0);
			// ����ʹ֮Ϊ0 
			// display(ROI, "ROI");

			// ������Ӿ����Ƿ�ɹ�
			resize(dst2, dst2, Size(800, 600));
			display(dst2, "resH");

			*/
		
		}
		//display(dst, "resH");
	}


	// չʾ��
	// dstΪԭ����һ��ͼ
	void displayWidth(priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpW>& myqueW, Mat &dst) {
		// ���ü�¼���ȣ��ж��Ƿ񶥸�ʹ֮��0��ʼ
		local = 0;
		// ��ʼ�������ĳ���
		new_line = 0;
		for (int i = 0; i < 20; i++) {
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
			// cout << height<<" "<< width<< endl;

			if (abs(height - avgHeight) > avgHeight / 3 || abs(width - avgWidth) > avgWidth / 2) {
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
	





			
			Mat rot_mat;
			float angle = 0;

			
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
			display(test_rot, "test_rot");
		//	imshow("test", final_test);
		//	waitKey(0);
			//cout<<contours[ConNum].size();
		//	clock_t e2 = clock();
		//	cout << "contours time:" << e2 - s2 << "ms" << endl;



			


			/*


			// �õ���ת�������ת�Ƕ�
			get_rotMat(res, rot_mat, angle, 1);
			// ������ת֮��P[0]��P[2]������
			pair<Point2f, Point2f> Q = caclAngle(angle, P, res);

			// �޸Ĺ���ͼƬ
			drawCon(dst1, ConNum, res);

			
			Mat dst2 = record[ConNum];
			//threshold(dst2, dst2, 244, 255, THRESH_BINARY);
			//dst2.convertTo(dst2, CV_8UC3);

			//Mat dst3;
			// display(dst2, "test2");
			//dst.copyTo(dst3, dst2);
			

			// ��ת֮���ͼ��
			Mat rot_image;
			warpAffine(dst2, rot_image, rot_mat, Size(dst2.size()));//ԭͼ����ת
																   // �õ�ÿһ�����ӵ�ͼ
		//	Mat ROI = rot_image(Rect(Q.first, Q.second));
			// ���ܵ�һ��ͼ 
			//putROI(ROI, 1);

			// ������Ӿ����Ƿ�ɹ�
			resize(dst2, dst2, Size(800, 600));
			display(dst2, "resw");
			*/
		}
	}
	
	// ����ǰ������ 
	// ConNum ��ǰ����������, ��ȥ���޹�����
	// dst Ϊ��Ҫȥ��������ͼ
	void drawCon(Mat &dst, int ConNum, RotatedRect &res) {
		size_t s = clock();
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
						dst.at<Vec3b>(j, i)[0] = 255;
						dst.at<Vec3b>(j, i)[1] = 255;
						dst.at<Vec3b>(j, i)[2] = 255;
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
		cvtColor(src, gray, CV_RGB2GRAY);
		GaussianBlur(gray, gray, Size(3, 3), 0, 0);
		// convert to binary
		threshold(gray, gray, 135, 255, THRESH_BINARY);
		// display(gray, "binary_pic");
		// RETR_CCOMP record outer and holes
		// CHAIN_APPROX_SIMPLE record conor points
		findContours(gray, contours, heierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
		// Ѱ��������
		//drawCon(dst);
		// Ѱ����Ӿ���
		findRect();
		cout << myqueH.size();
		pair<float, float> avg = caculateAvg(myqueH);
		avgHeight = avg.first;
		avgWidth = avg.second;
		cout << myqueH.size();
	    // cout << avgHeight << " " << avgWidth << endl;
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
	//	display(final_pic, "Weight");
	//	waitKey(0);
		
	}
public:	
	Mat& getImage(Mat &src, Mat& dst1) {
		// ��ʼ�����յĽ��ͼ
		final_pic = Mat(src.rows, src.cols, CV_8UC3, Scalar(0,0,0));
		// ���ƽ���ĸߺͿ�
		avgHeight = 0;
		avgWidth = 0;
		// ��ʼ����¼����λ��
		local = 0;
		offset = 0;
		//���һ��ͼ
		Rect rect_l, rect_r;
		rect_l = Rect(0, 0, src.cols/2, src.rows);
		rect_r = Rect(src.cols / 2, 0, src.cols-src.cols/2, src.rows);

		// ��ȡ�����ͼ
		Mat img_L = src(rect_l);
	//	cout << src.cols / 2 << " " << src.rows << endl;
	//	cout << dst1.rows << " " << dst1.cols << endl;
		dst_L = dst1(rect_l);
		
	//	SortSeed(img_L, dst_L);

	//	resize(dst_L, dst_L, Size(800, 600));
	//	display(dst_L, "left");

		// ��ն���
		while (!myqueH.empty()) {
			myqueH.pop();
		}
		while (!myqueW.empty()) {
			myqueW.pop();
		}
		// ������ֵר��
		record.clear();
	

		local = 0;
		offset = src.cols/2;
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
	double avgHeight, avgWidth;
	// local ��ʾÿ�����Ӵﵽ��ײ�Խ��ʱ���޸Ĳ���
	// offset ��ʾ�ұ����ӵ�ƫ����
	int local, offset;
	// ��¼ԭͼ, ��ԭͼ����ԭͼ
	Mat DST, dst_L, dst_R;
	// ÿ�γ����㹻������һ�п�ʼ
	int new_line;
	
	// ��¼�����Ƿ񱻴����
	vector<Mat> record;

	// ��¼��û�д������ͼ
	vector<bool> flag;

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
	src = imread("C://Myself//Dataset//rice//E24.jpg");
	dst = imread("C://Myself//Dataset//seed//D24.jpg");
//	resize(src, src, Size(src.cols / 2, src.rows / 2));
//	resize(dst, dst, Size(dst.cols / 2, dst.rows / 2));
	// exceptional 
	if (src.empty()) {
		cerr << "No image!";
		return -1;
	}
	// init object
	plantInfo seed;

	// display
	// pod.display(src, "ori");
	Mat final_test = seed.getImage(src, dst);
	imshow("final", final_test);
	waitKey(0);
	size_t end = clock();
	cout << end - start << "ms" << endl;
	return 0;
}