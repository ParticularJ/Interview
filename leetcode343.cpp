/*
Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.

Example 1:

Input: 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.
Example 2:

Input: 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
*/

class Solution {
private:
	int max3(int a, int b, int c) {
		return max3(max(a, b), c);
	}
public:
	int integerBreak(int n) {
		assert(n >= 2);
		// 设置记录值
		vector<int> memo(n + 1, -1);
		memo[1] = 1;
		memo[2] = 1;
		// 从3开始
		for (int i = 3; i <= n; i++)
			// 可以分割成1到i-1
			for (int j = 1; j <= i-1; j++)
				// 分别对比，取 当前的memo[i], 直接分割成j*(i-j),以及j*memo[i-j]的 最大值
				// 比如i=3, j=1时， max(memo[3], memo[3-1]*1, 1*(3-1))的 memo[3] = 2
				//  i=3, j=2时， max（memo[3], memo[3-2] * 1, 2*(3-2)得， memo[3] = 2
				memo[i] = max3(memo[i], memo[i - j] * j, j*(i - j));
		return memo[n];
	}
};