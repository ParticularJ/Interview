#include<opencv2\opencv.hpp>

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

class plantInfo {
public:
	plantInfo();
	~plantInfo();
	int getImage(cv::Mat &src, cv::Mat &dst, cv::Mat &final_pic);
private:
	// 记录平均的长和宽
	int a, b;
	double avgHeight, avgWidth;
	// local 表示每次种子达到最底层越界时的修改参数
	// offset 表示右边种子的偏移量
	int local, offset;
	// 每次长度足够，从新一行开始
	int new_line;
	void sort_record(std::pair<int, cv::RotatedRect> &rect);
	std::pair<float, float> caculateAvg(const std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH> H);
	void findRect(std::vector<std::vector<cv::Point>>& contours);
	void putROI(cv::Mat &roi, cv::Mat &final_pic,int flag);
	std::pair<cv::Point2f, cv::Point2f> caclAngle(float angle, cv::Point2f P[4], cv::Point2f &center);
	void get_rotMat(cv::RotatedRect& res, cv::Mat &rot_mat, cv::Point2f &center, float& angle, int flag);
	void displayHeight(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH>& myqueH, cv::Mat &dstH, cv::Mat &final_pic, std::vector<std::vector<cv::Point>>& contours);
	void displayWidth(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW>& myqueW, cv::Mat &dstW, cv::Mat &final_pic, std::vector<std::vector<cv::Point>>& contours);
	void SortSeed(cv::Mat &semi_src, cv::Mat &semi_dst, cv::Mat &final_pic);
};
