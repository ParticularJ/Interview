/*
Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.

Example 1:

Input: 2
Output: 1
Explanation: 2 = 1 + 1, 1 ¡Á 1 = 1.
Example 2:

Input: 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 ¡Á 3 ¡Á 4 = 36.
*/

class Solution {
private:
	int max3(int a, int b, int c) {
		return max(max(a, b), c);
	}
public:
	int integerBreak(int n) {
		assert(n >= 2);
		vector<int> memo(n + 1, -1);
		memo[1] = 1;
		memo[2] = 1;
		for (int i = 3; i <= n; i++)
			for (int j = 1; j < i; j++)
				memo[i] = max3(memo[i], memo[i - j] * j, j*(i - j));
		return memo[n];
	}
};