/*
��̬�滮���ֱ��¼2��3��5���ֵĴ���
*/

class Solution {
public:
	int nthUglyNumber(int n) {
		if (n == 1)return 1;
		vector<int> nums{ 1 };
		int t2 = 0, t3 = 0, t5 = 0;
		// �ж�������������û�дﵽn��
		while (nums.size() <= n) {
			int new_2 = nums[t2] * 2;
			int new_3 = nums[t3] * 3;
			int new_5 = nums[t5] * 5;
			//ȡ��Сֵ����֤�ǰ�����С�ĵ���
			int mina = min(new_2, min(new_3, new_5));
			if (mina == new_2)t2++;
			if (mina == new_3)t3++;
			if (mina == new_5)t5++;
			nums.push_back(mina);
		}
		return nums[n - 1];
	}
};