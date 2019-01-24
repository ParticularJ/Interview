#include<opencv2\opencv.hpp>
#include<fstream>

struct SeedInfo
{
	//编号
	int ID;
	//面积
	float sArea;
	//周长
	float sPerimeter;
	//长
	float sLength;
	//宽
	float sWide;
	//长/宽
	float sL1Wratio;
	//增加RGB颜色参数
	int sR;
	int sG;
	int sB;

	//有效种子为true
	int seedFlag;
	//有凸尖为true
	int plumuleFlag;
	//中心
	cv::Point centerPt;
	//圆中心最远点
	cv::Point maxDistPt;
	//角点1
	cv::Point pt1;
	//角点2
	cv::Point pt2;
	//角点3
	cv::Point pt3;
	//角点4
	cv::Point pt4;
	//该点轮廓大小
	int cSize;
	//该点轮廓
	cv::Point contour[250];
};


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
	plantInfo(int seed);
	~plantInfo();
	void simuStr(SeedInfo* seed);
	
	int getImage(cv::Mat &src, cv::Mat &dst, cv::Mat &final_pic, SeedInfo* seed);
private:
	// 记录别切割的x轴坐标
	int segloc;

	// 统计种子的个数
	int seedNum;
	// 按照长排还是宽排
	bool byHeightOrWidth;

	// 记录总长度，以及总宽度
	float totalHeight;
	float totalWidth;
	// 记录上下基准线位置
	int top_X;
	int top_Y;
	int bottom_X;
	int bottom_Y;

	// 记录结构体
	SeedInfo *seed_global;
	// 记录最终的长度
	void putLength(std::string name, float Length, cv::Mat &final_pic);
	// 记录平均的长和宽
	int a, b;
	double avgHeight, avgWidth, avgArea;
	// local 表示每次种子达到最底层越界时的修改参数
	// offset 表示右边种子的偏移量
	// offseth、w 表示长和宽得偏移量
	int local, offset, offsetw, offseth;
	// 每次长度足够，从新一行开始
	int new_line;
	void sort_record(std::pair<int, cv::RotatedRect> &rect);
	std::pair<std::pair<float, float>, float> caculateAvg(const std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH> H, std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW> W);
	void findRect();
	void putROI(cv::Mat &roi, cv::Mat &final_pic,int flag, int index);
	std::pair<cv::Point2f, cv::Point2f> caclAngle(float angle, cv::Point2f P[4], cv::Point2f &center);
	void get_rotMat(cv::RotatedRect& res, cv::Mat &rot_mat, cv::Point2f &center, float& angle, int flag);
	void displayHeight(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpH>& myqueH, cv::Mat &dstH, cv::Mat &final_pic);
	void displayWidth(std::priority_queue <std::pair<int, cv::RotatedRect>, std::vector<std::pair<int, cv::RotatedRect> >, cmpW>& myqueW, cv::Mat &dstW, cv::Mat &final_pic);
	void SortSeed(cv::Mat &semi_src, cv::Mat &semi_dst, cv::Mat &final_pic);
};
