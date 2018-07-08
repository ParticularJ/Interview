#include<iostream>
#include<vector>
#include<deque>

using namespace std;
/*
	˼·��һ���������Ȱ�������һ�ݣ�������������������������Ŀ�ʼ��֤��ȫ����һ��
	�� �� ABCDABCD
		 + + - - ++ --
	���۴���һ����ʼ������һ����
	ǰ׺�ͣ� �����Ŀ�ʼ����֤ÿһ���������������ļ���
	ʹ��˫�˶���,�������У�ά��һ������
*/

class Solution {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int size = gas.size();
		for (int i = 0; i < size; i++) {
			gas[i] -= cost[i];
		}

		// ת������������������
		vector<int> lian(size * 2, 0);
		lian[0] = gas[0];
		for (int i = 1; i < size; i++) lian[i] = lian[i-1] + gas[i];
		for (int i = size; i < 2 * size; i++)lian[i] = lian[i-1] + gas[i - size];
		// �洢id�;����ֵ
		deque<pair<int, int> > mini;
		int pre_sum = 0;
		for (int i = 0; i < size; i++) {
			// ����˫�˶���
			if (i == 0) {
				for (int i = 0; i < size; i++) {
					if (mini.size() == 0) {
						mini.push_back(make_pair(i, lian[i]));
					}
					else {
						// ������������
						while (mini.size() > 0 && mini.back().second > lian[i])
							mini.pop_back();
						mini.push_back(make_pair(i, lian[i]));
					}
				}
			}
			else {
				// ά��һ����Χ
				//  ����ʹ��һ�������������У�
				// ÿһλ�洢ǰ׺�ͣ� ����������ּ�ȥ��С��ǰ׺��Ϊ������ô���ǿ��е�
				if (mini.front().first == i - 1)
					mini.pop_front();
				while (mini.size() > 0 && mini.back().second > lian[i + size - 1])
					mini.pop_back();
				mini.push_back(make_pair(i + size - 1, lian[i + size - 1]));
			}
			if (mini.front().second - pre_sum >= 0)
				return i;
			pre_sum = lian[i];
		}
		return -1;
	}
};