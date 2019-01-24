#include<opencv2\opencv.hpp>
#include<fstream>

struct SeedInfo
{
	//���
	int ID;
	//���
	float sArea;
	//�ܳ�
	float sPerimeter;
	//��
	float sLength;
	//��
	float sWide;
	//��/��
	float sL1Wratio;
	//����RGB��ɫ����
	int sR;
	int sG;
	int sB;

	//��Ч����Ϊtrue
	int seedFlag;
	//��͹��Ϊtrue
	int plumuleFlag;
	//����
	cv::Point centerPt;
	//Բ������Զ��
	cv::Point maxDistPt;
	//�ǵ�1
	cv::Point pt1;
	//�ǵ�2
	cv::Point pt2;
	//�ǵ�3
	cv::Point pt3;
	//�ǵ�4
	cv::Point pt4;
	//�õ�������С
	int cSize;
	//�õ�����
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
	// ��¼���и��x������
	int segloc;

	// ͳ�����ӵĸ���
	int seedNum;
	// ���ճ��Ż��ǿ���
	bool byHeightOrWidth;

	// ��¼�ܳ��ȣ��Լ��ܿ��
	float totalHeight;
	float totalWidth;
	// ��¼���»�׼��λ��
	int top_X;
	int top_Y;
	int bottom_X;
	int bottom_Y;

	// ��¼�ṹ��
	SeedInfo *seed_global;
	// ��¼���յĳ���
	void putLength(std::string name, float Length, cv::Mat &final_pic);
	// ��¼ƽ���ĳ��Ϳ�
	int a, b;
	double avgHeight, avgWidth, avgArea;
	// local ��ʾÿ�����Ӵﵽ��ײ�Խ��ʱ���޸Ĳ���
	// offset ��ʾ�ұ����ӵ�ƫ����
	// offseth��w ��ʾ���Ϳ��ƫ����
	int local, offset, offsetw, offseth;
	// ÿ�γ����㹻������һ�п�ʼ
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
