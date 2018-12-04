/*
Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.

Example 1:

Input: 2
Output: 1
Explanation: 2 = 1 + 1, 1 �� 1 = 1.
Example 2:

Input: 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 �� 3 �� 4 = 36.
*/

class Solution {
private:
	int max3(int a, int b, int c) {
		return max3(max(a, b), c);
	}
public:
	int integerBreak(int n) {
		assert(n >= 2);
		// ���ü�¼ֵ
		vector<int> memo(n + 1, -1);
		memo[1] = 1;
		memo[2] = 1;
		// ��3��ʼ
		for (int i = 3; i <= n; i++)
			// ���Էָ��1��i-1
			for (int j = 1; j <= i-1; j++)
				// �ֱ�Աȣ�ȡ ��ǰ��memo[i], ֱ�ӷָ��j*(i-j),�Լ�j*memo[i-j]�� ���ֵ
				// ����i=3, j=1ʱ�� max(memo[3], memo[3-1]*1, 1*(3-1))�� memo[3] = 2
				//  i=3, j=2ʱ�� max��memo[3], memo[3-2] * 1, 2*(3-2)�ã� memo[3] = 2
				memo[i] = max3(memo[i], memo[i - j] * j, j*(i - j));
		return memo[n];
	}
};