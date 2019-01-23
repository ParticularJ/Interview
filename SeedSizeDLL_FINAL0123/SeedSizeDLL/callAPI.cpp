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

int __stdcall getImage(int seedNum, uchar* dst_data, int dst_width, int dst_height, int dst_step, uchar* pfinal_pic, SeedInfo* seedInfo) {
	// ��ʼ����
	plantInfo seed(seedNum);
	
	// ����src��Ӧ��ֵͼ��
	// dst ��Ӧԭͼ
	// SeedSizeImg ��Ӧ���������Сͼ
	cv::Mat src(dst_height, dst_width, CV_8UC1, cv::Scalar(0));
	cv::Mat dst(dst_height, dst_width, CV_8UC3, dst_data, dst_step);
	cv::Mat SeedSizeImg;
	// ������Ӵ�Сͼ
	/*cv::imshow("src", src);
	cv::waitKey(0);
	cv::imshow("dst", dst);
	cv::waitKey(0);*/

	
	for (int i = 0; i < 4; i++) {
		// ����
		std::vector<std::vector<cv::Point>> contours(4, std::vector<cv::Point>());
		if (seedInfo[i].sLength == 0 && seedInfo[i].sWide == 0)
			break;
		else {
			for (int j = 0; j < 250; j++) {
				if (seedInfo[i].contour[j].x == 0 && seedInfo[i].contour[j].y == 0)
					break;
				contours[i].push_back(cv::Point(seedInfo[i].contour[j].x, seedInfo[i].contour[j].y));
			}
			
			// ����Ϊ��0�� 0��,����ѭ��
			cv::drawContours(src, contours, i, cv::Scalar(255), -1);
			// cv::resize(src, src, cv::Size(800, 600));
			
		}
	}
//	cv::resize(src, src, cv::Size(800, 600));
	cv::imshow("src", src);
	cv::imwrite("./1.jpg", src);
	cv::waitKey(0);
	

	

	int res = seed.getImage(src, dst, SeedSizeImg, seedInfo);
	
	cv::cvtColor(SeedSizeImg, SeedSizeImg, CV_BGR2BGRA);

	// ��ȡfinal������ڴ�
	int size = 4 * SeedSizeImg.rows*SeedSizeImg.cols;
	// ���õ���matͼ����һ��
	memcpy(pfinal_pic, SeedSizeImg.data, size);
	return 1;
}


