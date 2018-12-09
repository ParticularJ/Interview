/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.
Example 2:

Input: [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
Total amount you can rob = 2 + 9 + 1 = 12.
*/

class Solution {
public:
	int rob(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)
			return 0;
		vector<int> memo(size, -1);
		memo[0] = nums[0];
		memo[1] = max(memo[0], nums[1]);
		for (int i = 2; i < size; i++) {
			// 偷取当前的和当前-2， 或者不偷当前，偷取当前-1
			memo[i] = max(memo[i] + memo[i-2], memo[i-1]);
		}
		return memo[size - 1];
	}
public:
	int rob2(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)
			return 0;
		vector<int> memo(size, -1);

		// 倒着来
		memo[size - 1] = nums[size - 1];
		if(size>=2)
			memo[size - 2] = max(memo[size - 1], nums[size - 2]);
		for (int i = size - 3; i >= 0; i--) {
			memo[i] = max(nums[i] + memo[i + 2], memo[i + 1]);
		}
		return memo[0];
	}
};
