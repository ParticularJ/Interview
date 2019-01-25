#include"callDLL.h"

/*
C++ �ӿ�
����ֱ�Ӵ���C#�Ĳ�����ͨ���˺���תΪC++��������Ĳ�������
parameters:
dst_data: ���ӵ�ԭͼ����
dst_width : ԭͼ�Ŀ�
dst_height: ԭͼ�ĸ�
dst_step: ԭͼ�Ĳ���
pfinal_pic: �õ�ͼ��dataָ��
*/


// seedNum ���Ӹ���

int __stdcall getImage(int seedNum, uchar* dst_data, int dst_width, int dst_height, int dst_step, uchar* pfinal_pic, SeedInfo* seedInfo) {
	// ��ʼ����
	plantInfo seed(seedNum);

	// ����src��Ӧ��ֵͼ��
	// dst ��Ӧԭͼ
	// SeedSizeImg ��Ӧ���������Сͼ
	cv::Mat src(dst_height, dst_width, CV_8UC1, cv::Scalar(0));
	// cv::Mat src = cv::imread("5.jpg", 0);
	cv::Mat dst(dst_height, dst_width, CV_8UC3, dst_data, dst_step);
	cv::Mat SeedSizeImg;
	// ������Ӵ�Сͼ
	/*cv::imshow("src", src);
	cv::waitKey(0);
	cv::imshow("dst", dst);
	cv::waitKey(0);*/


	for (int i = 0; i < 2000; i++) {
		// ����
		std::vector<std::vector<cv::Point>> contours(2000, std::vector<cv::Point>());
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
		}
	}

	cv::imwrite("./binary.jpg", src);
	//	cv::imwrite("./ori.jpg", dst);


	int res = seed.getImage(src, dst, SeedSizeImg, seedInfo);

	cv::cvtColor(SeedSizeImg, SeedSizeImg, CV_BGR2BGRA);

	// ��ȡfinal������ڴ�
	int size = 4 * SeedSizeImg.rows*SeedSizeImg.cols;
	// ���õ���matͼ����һ��
	memcpy(pfinal_pic, SeedSizeImg.data, size);
	return 1;
}


