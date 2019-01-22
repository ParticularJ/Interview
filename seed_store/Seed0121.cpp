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
	// 显示图片
	void display(Mat& src, string name) {
		namedWindow(name, WINDOW_NORMAL);
		imshow(name, src);
		waitKey(0);
	}

	// 记录高、宽
	void sort_record(pair<int, RotatedRect> &rect) {
		myqueW.push(rect);
		myqueH.push(rect);
	}

	// 计算平均高和宽 和 平均面积
	// cont为传进来的轮廓图
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
		//计算平均长
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


	// 寻找外接矩形
	void findRect(Mat &dst1) {
		record = vector<Mat>(contours.size(), Mat());
		for (size_t i = 0; i < contours.size(); i++) {
			RotatedRect rect = minAreaRect(contours[i]);

			Point2f P[4];
			rect.points(P);
			// 绘制出轮廓
			//for (int j = 0; j <= 3; j++)
			//{
			//	//	//cout << P[j];
			//	line(dst1, P[j], P[(j + 1) % 4], Scalar(255, 0, 255), 2);

			//}
			// rect.boundingRect
			// 分别对高和宽进行排序
			sort_record(make_pair(static_cast<int>(i), rect));
		}
	}

	// 将结果放入同一张图中
	// flag 0 为长，1为宽
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
		// 上基准线
		line(final_pic, Point(top_X, top_Y), Point(top_X + 100, top_Y), Scalar(0, 0, 255), 5);
	
		// 下基准线
		bottom_X = top_X;
		bottom_Y = (bottom_Y == 0) ? local : bottom_Y;
		line(final_pic, Point(bottom_X, bottom_Y), Point(bottom_X + 100, bottom_Y), Scalar(0, 0, 255), 5);

		// 中心线上半段
		// x坐标
		int semit_cenX = top_X + 50;
		// y坐标开始位置
		int semit_cenY = top_Y;
		// y坐标结束位置
		int y_end = static_cast<int>((top_Y + bottom_Y) / 2);
		line(final_pic, Point(semit_cenX, semit_cenY), Point(semit_cenX, y_end-20), Scalar(0, 0, 255), 3);

		// 中心线下半段

		line(final_pic, Point(semit_cenX, y_end+20), Point(semit_cenX, bottom_Y), Scalar(0, 0, 255), 3);
		
		// 书写总长度
		putText(final_pic, name + to_string(Length) + "mm", Point(semit_cenX-100, y_end + 15), 2, 1, Scalar(0, 0, 255), 2);

		bottom_Y = 0;
	}


	//计算旋转后的坐标
	pair<Point2f, Point2f> caclAngle(float angle, Point2f P[4], RotatedRect& res) {
		// 计算旋转之后P[0]与P[2]的坐标
		Point2f Q[2];
		float angle_arc = static_cast<float>(PI / 180.0 * angle);

		//  绕某个中心的旋转公式
		Q[0].x = (P[0].x - res.center.x)*cos(angle_arc) - (res.center.y - P[0].y)*sin(angle_arc) + res.center.x;
		Q[0].y = res.center.y - (P[0].x - res.center.x)*sin(angle_arc) - (res.center.y - P[0].y)*cos(angle_arc);
		Q[1].x = (P[2].x - res.center.x)*cos(angle_arc) - (res.center.y - P[2].y)*sin(angle_arc) + res.center.x;
		Q[1].y = res.center.y - (P[2].x - res.center.x)*sin(angle_arc) - (res.center.y - P[2].y)*cos(angle_arc);
		return make_pair(Q[0], Q[1]);
	}

	// test 旋转矩阵
	pair<Point2f, Point2f> caclAngle(float angle, Point2f P[4], Point2f &center) {
		// 计算旋转之后P[0]与P[2]的坐标
		Point2f Q[2];
		float angle_arc = static_cast<float>(PI / 180.0 * angle);

		//  绕某个中心的旋转公式
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

	//  test 得到旋转矩阵以及角度

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





	// 展示高
	// dst为对应的原图
	void displayHeight(priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpH>& myqueH, Mat &dst) {
		// 初始化顶格后新的行
		new_line = 20;
		top_Y = new_line;
		for (int i = 0; i < seedNum; i++) {
		//	clock_t s2 = clock();
			// 拷贝一份新图
			Mat dst1 = dst.clone();
		//	display(dst1, "dst1");
			pair<int, RotatedRect> front = myqueH.top();
			//	取出最大的数据
			RotatedRect res = front.second;
			// 轮廓的位置坐标
			int ConNum = front.first;
		//	cout << "The area:" << res.size.area() << endl;
			Point2f P[4];
			res.points(P);
			// 绘制出轮廓
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
				// 展示错误图像
				for (int j = 0; j <= 3; j++) {
					//	//	//cout << P[j];
					line(dst1, P[j], P[(j + 1) % 4], Scalar(0, 255, 0), 3);
				}
				// resize(dst1, dst1, Size(800, 600));
				display(dst1, "error1");
				i--;
				continue;
			}

			// 根据凸包与周长之比
			
			convexHull(contours[ConNum], hull[ConNum], false);
			double convexLength = arcLength(hull[ConNum], true);
			double contoursLength = arcLength(contours[ConNum], true);
		//	cout << "凸包长：" << convexLength << " " << "轮廓长： " << contoursLength << endl;

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
			// 旋转图像
			// 定义旋转矩阵
			Mat rot_mat;
			float angle = 0;

			



			/*

			// 测试分割开旋转，截取
		//	clock_t s2 = clock();
			Mat mask, seg_mat, seg_final;
			// 获得mask
			mask = dst1(Rect(res.boundingRect().tl(), res.boundingRect().br()));
			seg_mat = mask.clone();
			// 计算便宜，使得图像都从左上角开始
			int off_x = res.boundingRect().tl().x ;
			int off_y = res.boundingRect().tl().y ;
			
			// 计算轮廓的偏移量
			for (int i = 0; i < contours[ConNum].size(); i++) {
				contours[ConNum][i].x -= off_x;
				contours[ConNum][i].y -= off_y;
			}
			flag[ConNum] = 1;

			clock_t t = clock();
			// 以填充的方式画出轮廓，形成最后的mask图
			drawContours(mask, contours, ConNum, Scalar(255, 255, 255), -1);
			cvtColor(mask, mask, CV_RGB2GRAY);
			threshold(mask, mask, 254, 255, THRESH_BINARY);
			Mat mask1 = ~mask;
			Mat back(mask.rows, mask.cols, CV_8UC1, Scalar(125));
			mask1 &= back;
			

			clock_t e = clock();
			cout << e - t << "ms" << endl;
			// 二值图转为三通道图
			// mask.convertTo(mask, CV_8UC3);
			cvtColor(mask, mask, CV_GRAY2RGB);
			cvtColor(mask1, mask1, CV_GRAY2RGB);
			cout << mask.channels() << " " << mask1.channels() << endl;

			display(mask, "mask");
			display(mask1, "mask1");
			
			// 进行切割
			seg_mat.copyTo(seg_final, mask);
			display(seg_final, "mask");

			
			add(seg_final, mask1, seg_final);

 			// 扩充，防止旋转时候越界
			int border = 70;
			copyMakeBorder(seg_final, seg_final, border, border, border, border, BORDER_CONSTANT, Scalar(0, 0, 0));
			



			// 得到旋转矩阵和旋转角度
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

			// 得到旋转矩阵和旋转角度
			get_rotMat(res, rot_mat, angle, 0);
			
			// 得到ROI所需的左上角和右下角的点
			pair<Point2f, Point2f> Q = caclAngle(angle, P, res);

			// 修改过后图片
			drawCon(dst1, ConNum, res);
		//	display(dst1, "dst1");
			// 修改过的图
			Mat dst2 = record[ConNum];
			//threshold(dst2, dst2, 244, 255, THRESH_BINARY);
			//Mat dst3;
			//dst2.convertTo(dst2, CV_8UC3);
		
			//dst.copyTo(dst3, dst2);
	
		//	display(dst3, "test1");
		//	display(dst2, "dst2");

			// 旋转之后的图像
	
			Mat rot_image;
			warpAffine(dst2, rot_image, rot_mat, Size(dst2.size()));//原图像旋转

			// 得到每一个种子的图
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
			// 汇总到一张图 
		    putROI(ROI, 0, ConNum);
			// 重置使之为0 
			// display(ROI, "ROI");
			// 测试外接矩形是否成功
			resize(dst2, dst2, Size(800, 600));
			display(dst2, "resH");

			
		}
		putLength("H:", totalHeight);
		offset = final_pic.cols / 2 + offsetw;
		//display(dst, "resH");
	}


	// 展示宽
	// dst为原来的一半图
	void displayWidth(priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpW>& myqueW, Mat &dst) {
		// 重置记录长度，判断是否顶格，使之从0开始
		local = 20;

		// 记录标定线的Y值
		top_Y = local;
		// 初始化顶格后的长度
		new_line = 20;
		for (int i = 0; i < seedNum; i++) {
			Mat dst1 = dst.clone();
			// 记录信息
			pair<int, RotatedRect> front = myqueW.top();
			// 旋转矩阵信息
			RotatedRect res = front.second;
			// contours 信息
			int ConNum = front.first;
			Point2f P[4];
			res.points(P);


		//	cout << "The angle is:" << res.angle << endl;
			// 绘制外接矩形
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
				// 展示错误图像
				for (int j = 0; j <= 3; j++){
				//	//	//cout << P[j];
					line(dst1, P[j], P[(j + 1) % 4], Scalar(0, 255, 0), 3);
				}
			//	resize(dst1, dst1, Size(800, 600));
				display(dst1, "error2");
				i--;
				continue;
			}

			// 根据凸包与周长之比

			convexHull(contours[ConNum], hull[ConNum], false);
			double convexLength = arcLength(hull[ConNum], true);
			double contoursLength = arcLength(contours[ConNum], true);
		//	cout << "凸包长：" << convexLength << " " << "轮廓长： " << contoursLength << endl;

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

			// 总宽度
			totalWidth += width;

			// 旋转矩阵和旋转角度
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


			// 得到旋转矩阵和旋转角度
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

			


			


			// 得到旋转矩阵和旋转角度
			get_rotMat(res, rot_mat, angle, 1);
			// 计算旋转之后P[0]与P[2]的坐标
			pair<Point2f, Point2f> Q = caclAngle(angle, P, res);

			// 修改过后图片
			drawCon(dst1, ConNum, res);

			
			Mat dst2 = record[ConNum];
		//	display(dst2, "dst2");
			//threshold(dst2, dst2, 244, 255, THRESH_BINARY);
			//dst2.convertTo(dst2, CV_8UC3);

			//Mat dst3;
			// display(dst2, "test2");
			//dst.copyTo(dst3, dst2);
		

			// 旋转之后的图像
			Mat rot_image;
			warpAffine(dst2, rot_image, rot_mat, Size(dst2.size()));//原图像旋转
																   // 得到每一个种子的图
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


		

			// 汇总到一张图 
			putROI(ROI, 1, ConNum);
		
			// 测试外接矩形是否成功
			resize(dst2, dst2, Size(800, 600));
			display(dst2, "resw");
			
		}
		putLength("W:", totalWidth);
		offset = 20;
	}
	
	// 画当前的轮廓 
	// ConNum 当前的轮廓坐标, 并去除无关区域
	// dst 为需要去除背景的图
	void drawCon(Mat &dst, int ConNum, RotatedRect &res) {
		Mat dst1 = dst.clone();
		// 记录旋转外接矩形
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
		// 旋转外接矩形
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
	// 对种子进行排序，src为二值图（左或者右）
	// dst为相应的原图（左或者右）
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
		// 寻找外轮廓
		// drawCon(dst);
		// 寻找外接矩形
		findRect(dst);
		//cout << myqueH.size();
		pair<pair<float, float>, float> avg = caculateAvg(myqueH, myqueW);
		avgHeight = avg.first.first;
		avgWidth = avg.first.second;
		avgArea = avg.second;
		//cout << myqueH.size();
	    cout << "avgHeight: "<<avgHeight << " avgWidth: " << avgWidth <<" avgArea: "<<avgArea<< endl;
		// 打印高
		// printQue(myqueH);
		// 展示高
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
		// 初始化最终的结果图
		final_pic = Mat(2518, 3469, CV_8UC3, Scalar(125,125,125));
		// 获得平均的高和宽
		avgHeight = 0;
		avgWidth = 0;
		avgArea = 0;
		offsetw = 0;
		offseth = 0;
		// 初始化记录长的位置
		local = 20;
		offset = 20;
		//获得一半图
		Rect rect_l, rect_r;
		rect_l = Rect(0, 0, src.cols/2, src.rows);
		rect_r = Rect(src.cols / 2, 0, src.cols-src.cols/2, src.rows);

		


		// 获取左半张图
		Mat img_L = src(rect_l);
	//	cout << src.cols / 2 << " " << src.rows << endl;
	//	cout << dst1.rows << " " << dst1.cols << endl;
		dst_L = dst1(rect_l);
		
		SortSeed(img_L, dst_L);

	//	resize(dst_L, dst_L, Size(800, 600));
	//	display(dst_L, "left");

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


		// 测试阈值专用
		record.clear();
	

		local = 20;
		offsetw = 870;
		offseth = 870;
		offset += offseth;
		// 获取右半张图
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
	// 记录平均的长和宽
	double avgHeight, avgWidth, avgArea;
	// local 表示每次种子达到最底层越界时的修改参数
	// offset 表示右边种子的偏移量
	int local, offset, offsetw, offseth;
	// 记录原图, 左原图，右原图
	Mat DST, dst_L, dst_R;
	// 每次长度足够，从新一行开始
	int new_line;
	
	// 统计种子的个数
	int seedNum;
	// 按照长排还是宽排
	bool byHeightOrWidth;

	// 记录总长度，以及总宽度
	int totalHeight;
	int totalWidth;
	// 记录上下基准线位置
	int top_X;
	int top_Y;
	int bottom_X;
	int bottom_Y;



	// 记录矩形是否被处理过
	vector<Mat> record;

	// 记录有没有处理过该图
	vector<bool> flag;
	
	// 记录凸包
	vector<vector<Point>> hull;
	// 记录轮廓
	vector<vector<Point>> contours;
	// 创立新图
	Mat final_pic;
	// 记录heierarchy
	vector<Vec4i> heierarchy;
	// 记录高
	priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpH> myqueH;
	// 记录宽
	priority_queue <pair<int, RotatedRect>, vector<pair<int, RotatedRect> >, cmpW> myqueW;
};

int main() {
	size_t start = clock();
	// Input Image
	Mat src, dst;
	// 水稻
//	dst = imread("a1_src1.jpg");
//	src = imread("1.jpg");
	// 玉米	
//	dst = imread("a1_src0.jpg");
//	src = imread("2.jpg");

	// 测试图片集
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