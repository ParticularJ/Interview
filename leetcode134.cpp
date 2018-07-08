#include<iostream>
#include<vector>
#include<deque>

using namespace std;
/*
	思路：一个环，首先把他拷贝一份，组成两个链表，这样可以随便从哪开始保证，全部走一遍
	如 ： ABCDABCD
		 + + - - ++ --
	无论从哪一个开始均能走一个环
	前缀和： 随便从哪开始，保证每一步运算结果都是正的即可
	使用双端队列,单调队列，维护一个区间
*/

class Solution {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int size = gas.size();
		for (int i = 0; i < size; i++) {
			gas[i] -= cost[i];
		}

		// 转换成连起来的两条链
		vector<int> lian(size * 2, 0);
		lian[0] = gas[0];
		for (int i = 1; i < size; i++) lian[i] = lian[i-1] + gas[i];
		for (int i = size; i < 2 * size; i++)lian[i] = lian[i-1] + gas[i - size];
		// 存储id和具体的值
		deque<pair<int, int> > mini;
		int pre_sum = 0;
		for (int i = 0; i < size; i++) {
			// 构建双端队列
			if (i == 0) {
				for (int i = 0; i < size; i++) {
					if (mini.size() == 0) {
						mini.push_back(make_pair(i, lian[i]));
					}
					else {
						// 单调递增队列
						while (mini.size() > 0 && mini.back().second > lian[i])
							mini.pop_back();
						mini.push_back(make_pair(i, lian[i]));
					}
				}
			}
			else {
				// 维持一个范围
				//  我们使用一个单调递增序列，
				// 每一位存储前缀和， 我们如果发现减去最小的前缀和为正，那么就是可行的
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