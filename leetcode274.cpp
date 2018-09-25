/*
桶排序
*/

class Solution {
public:
	int hIndex(vector<int>& citations) {
	//	sort(citations.begin(), citations.end());
		int size = citations.size();
		vector<int> bucket(size + 1, 0);
		for (auto i：citations)
			// 大于论文个数的分为一类
			bucket[min(i,size)] += 1;

		int temp;
		for (int i = size - 1; i >= 0; i--) {
			

			if (temp + bucket[i] >= i)
				return i;
			else
				temp += bucket[i];
		}
	}
};