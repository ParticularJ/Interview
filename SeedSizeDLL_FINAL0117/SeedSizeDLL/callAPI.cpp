#include"callDLL.h"

/*
	C++ �ӿ�
	����ֱ�Ӵ���C#�Ĳ�����ͨ���˺���תΪC++��������Ĳ�������
parameters:
	src_data: ���ӵĶ�ֵͼ����
	src_width: ��ֵͼ�Ŀ�
	src_height: ��ֵͼ�ĸ�
	src_step: ��ֵͼ�Ĳ���
	dst_data: ���ӵ�ԭͼ����
	dst_width : ԭͼ�Ŀ�
	dst_height: ԭͼ�ĸ�
	dst_step: ԭͼ�Ĳ���
	pfinal_pic: �õ�ͼ��dataָ��
*/


// seedNum ���Ӹ���
// sortByHeightOrWidth: true���ճ��ţ�false���տ��� 

int __stdcall simuStr(SeedInfo *seedInfo) {
	plantInfo seed;
	seed.simuStr(seedInfo);
	return 1;
}

int __stdcall getImage(int seedNum, bool sortByHeightOrWidth, uchar* src_data, int src_width, int src_height, int src_step, uchar* dst_data, int dst_width, int dst_height, int dst_step, uchar* pfinal_pic, SeedInfo* seedInfo) {
	
	plantInfo seed(seedNum, sortByHeightOrWidth);
	
	// ����src��Ӧ��ֵͼ��
	// dst ��Ӧԭͼ
	// SeedSizeImg ��Ӧ���������Сͼ
	cv::Mat src(src_height, src_width, CV_8UC1, src_data, src_step);
	cv::Mat dst(dst_height, dst_width, CV_8UC3, dst_data, dst_step);
	cv::Mat SeedSizeImg;
	// ������Ӵ�Сͼ
	/*cv::imshow("src", src);
	cv::waitKey(0);
	cv::imshow("dst", dst);
	cv::waitKey(0);*/

	int res = seed.getImage(src, dst, SeedSizeImg, seedInfo);
	
	cv::cvtColor(SeedSizeImg, SeedSizeImg, CV_BGR2BGRA);

	// ��ȡfinal������ڴ�
	int size = 4 * SeedSizeImg.rows*SeedSizeImg.cols;
	// ���õ���matͼ����һ��
	memcpy(pfinal_pic, SeedSizeImg.data, size);
	return 1;
}

